/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "header.h"

#define OP_EOF    0x66
#define OP_POS    0x65
#define OP_ACOS   0x64
#define OP_ASIN   0x63
#define OP_ATAN   0x62
#define OP_SQRT   0x61
#define OP_EXP    0x60
#define OP_LN     0x5f
#define OP_TAN    0x5e
#define OP_COS    0x5d
#define OP_SIN    0x5c
#define OP_CSNG   0x5b
#define OP_CINT   0x5a
#define OP_ALLOC  0x59
#define OP_SGN    0x58
#define OP_RND    0x57
#define OP_ABS    0x56
#define OP_INP    0x55
#define OP_DPEEK  0x54
#define OP_FRE    0x53
#define OP_FLG    0x52
#define OP_PEEK   0x51
#define OP_MOD    0x43
#define OP_MUL    0x42
#define OP_DIV    0x41
#define OP_ADD    0x32
#define OP_SUB    0x31
#define OP_GT     0x26
#define OP_LT     0x25
#define OP_GTE    0x24
#define OP_LTE    0x23
#define OP_EQ     0x22
#define OP_NE     0x21
#define OP_AND    0x13
#define OP_OR     0x12
#define OP_XOR    0x11
#define OP_OP     0x08
#define OP_CP     0x09
char    opType;

typedef union {
  dword i;
  float f;
  } FPI;

char* isFloatingPointNumber(char* line, char* token) {
  char  flag;
  char  dot;
  char* oline;
  char *otoken;
  oline = line;
  otoken = token;
  flag = 0;
  dot = 0;
  if (*line == '-') *token++ = *line++;
  while (flag == 0) {
    if (*line >= '0' && *line <= '9') *token++ = *line++;
    else if (*line == '.' && dot == 0) {
      *token++ = *line++;
      dot = 1;
      }
    else if (*line == '.') {
      showError("Syntax error");
      exprErrors++;
      *line = 0;
      return line;
      }
    else flag = 2;
    }
  if (*line >= 'a' && *line <= 'z') flag = 1;
  if (*line >= 'A' && *line <= 'Z') flag = 1;
  if (dot == 0) flag = 1;
  if (flag == 1) {
    line = oline;
    token = otoken;
    }
  *token = 0;
  return line;
  }

char* isIntegerNumber(char* line, char* token) {
  char  flag;
  char* oline;
  char *otoken;
  oline = line;
  otoken = token;
  flag = 0;
  if (*line == '-') *token++ = *line++;
  while (flag == 0) {
    if (*line >= '0' && *line <= '9') *token++ = *line++;
    else flag = 2;
    }
  if (*line >= 'a' && *line <= 'z') flag = 1;
  if (*line >= 'A' && *line <= 'Z') flag = 1;
  if (flag == 1) {
    line = oline;
    token = otoken;
    }
  *token = 0;
  return line;
  }

char* isIntegerVariable(char* line, char* token) {
  char  flag;
  char* oline;
  char *otoken;
  oline = line;
  otoken = token;
  flag = 0;
  while (flag == 0) {
    if ((*line >= 'a' && *line <= 'z') ||
        (*line >= 'A' && *line <= 'Z') ||
        (*line >= '0' && *line <= '9') ||
         *line == '_') *token++ = *line++;
    else flag = 2;
    }
  if (*line == '!') flag = 1;
  if (flag == 1) {
    line = oline;
    token = otoken;
    }
  *token = 0;
  return line;
  }

void check2args() {
  if (tokens[numTokens-1] == tokens[numTokens-4]) {
    opType = (tokens[numTokens-1] == OP_NUM) ? 'I' : 'F';
    return;
    }
  if (tokens[numTokens-1] == OP_NUMFP && tokens[numTokens-4] == OP_NUM) {
    Asm("           inc     r7                  ; Convert first number to floating point");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           sep     scall");
    Asm("           dw      itof");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           dec     r7");
    AddExternal(currentProc, "itof");
    tokens[numTokens-4] = OP_NUMFP;
    opType = 'F';
    }
  if (tokens[numTokens-1] == OP_NUM && tokens[numTokens-4] == OP_NUMFP) {
    Asm("           sep     scall               ; Convert second number to floating point");
    Asm("           dw      itof");
    AddExternal(currentProc, "itof");
    tokens[numTokens-1] = OP_NUMFP;
    opType = 'F';
    }
  }

int reduce(char last) {
  int arg1,arg2;
  int op;
  int ret;
  if (numTokens == 0) return 0;
  if (tokens[numTokens-1] != OP_NUM && tokens[numTokens-1] != OP_NUMFP) return 0;
  opType = 'I';
  if (numTokens > 2 && tokens[numTokens-3] >= 0x50) {
    opType = (tokens[numTokens-1] == OP_NUM) ? 'I' : 'F';
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (last) ret = -1;
    }
  else if (numTokens > 2 && tokens[numTokens-3] == OP_OP) {
    opType = (tokens[numTokens-1] == OP_NUM) ? 'I' : 'F';
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (numTokens > 0 && tokens[numTokens-1] >= 0x50) ret = -1;
    if (last) ret = -1;
    }
  else if (numTokens > 4 && tokens[numTokens-3] >= 0x10 &&
                            (tokens[numTokens-4] == OP_NUM ||
                             tokens[numTokens-4] == OP_NUMFP)) {
    check2args();
    arg2 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    arg1 = tokens[numTokens-5];
    numTokens -= 5;
    ret = -1;
    }
  else {
    return 0;
    }
  switch (op) {
    case OP_SGN:
         Asm("           sep     scall               ; Perform SGN()");
         if (opType == 'F') {
           Asm("           dw      sgnfp");
           AddExternal(currentProc, "sgnfp");
           }
         else if (use32Bits) {
           Asm("           dw      sgn32");
           AddExternal(currentProc, "sgn32");
           }
         else {
           Asm("           dw      sgn16");
           AddExternal(currentProc, "sgn16");
           }
         if (opType == 'F') opType = 'I';
         break;
    case OP_RND:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           sep     scall               ; Perform RND()");
         if (use32Bits) {
           Asm("           dw      rnd32");
           AddExternal(currentProc, "rnd32");
           useLfsr = -1;
           }
         else {
           Asm("           dw      rnd16");
           AddExternal(currentProc, "rnd16");
           useLfsr = -1;
           }
         break;
    case OP_ABS:
         Asm("           sep     scall               ; Perform ABS()");
         if (opType == 'F') {
           Asm("           dw      absfp");
           AddExternal(currentProc, "absfp");
           }
         else if (use32Bits) {
           Asm("           dw      abs32");
           AddExternal(currentProc, "abs32");
           }
         else {
           Asm("           dw      abs16");
           AddExternal(currentProc, "abs16");
           }
         break;
    case OP_MUL:
         Asm("           sep     scall               ; Perform multiplication");
         if (opType == 'F') {
           Asm("           dw      mulfp");
           AddExternal(currentProc, "mulfp");
           }
         else if (use32Bits) {
           Asm("           dw      mul32");
           AddExternal(currentProc, "mul32");
           }
         else {
           Asm("           dw      mul16");
           AddExternal(currentProc, "mul16");
           }
         break;
    case OP_DIV:
         Asm("           sep     scall               ; Perform division");
         if (opType == 'F') {
           Asm("           dw      divfp");
           AddExternal(currentProc, "divfp");
           }
         else if (use32Bits) {
           Asm("           dw      div32");
           AddExternal(currentProc, "div32");
           }
         else {
           Asm("           dw      div16");
           AddExternal(currentProc, "div16");
           }
         break;
    case OP_MOD:
         Asm("           sep     scall               ; Perform modulo");
         if (use32Bits) {
           Asm("           dw      mod32");
           AddExternal(currentProc, "mod32");
           }
         else {
           Asm("           dw      mod16");
           AddExternal(currentProc, "mod16");
           }
         break;
    case OP_ADD:
         Asm("           sep     scall               ; Perform addition");
         if (opType == 'F') {
           Asm("           dw      addfp");
           AddExternal(currentProc, "addfp");
           }
         else if (use32Bits) {
           Asm("           dw      add32");
           AddExternal(currentProc, "add32");
           }
         else {
           Asm("           dw      add16");
           AddExternal(currentProc, "add16");
           }
         break;
    case OP_SUB:
         Asm("           sep     scall               ; Perform subtraction");
         if (opType == 'F') {
           Asm("           dw      subfp");
           AddExternal(currentProc, "subfp");
           }
         else if (use32Bits) {
           Asm("           dw      sub32");
           AddExternal(currentProc, "sub32");
           }
         else {
           Asm("           dw      sub16");
           AddExternal(currentProc, "sub16");
           }
         break;
    case OP_GT :
         Asm("           sep     scall               ; Perform greater than");
         if (opType == 'F') {
           Asm("           dw      gtfp");
           opType = 'I';
           AddExternal(currentProc, "gtfp");
           }
         else if (use32Bits) {
           Asm("           dw      gt32");
           AddExternal(currentProc, "gt32");
           }
         else {
           Asm("           dw      gt16");
           AddExternal(currentProc, "gt16");
           }
         break;
    case OP_LT :
         Asm("           sep     scall               ; Perform less than");
         if (opType == 'F') {
           Asm("           dw      ltfp");
           opType = 'I';
           AddExternal(currentProc, "ltfp");
           }
         else if (use32Bits) {
           Asm("           dw      lt32");
           AddExternal(currentProc, "lt32");
           }
         else {
           Asm("           dw      lt16");
           AddExternal(currentProc, "lt16");
           }
         break;
    case OP_GTE:
         Asm("           sep     scall               ; Perform greater or equal");
         if (opType == 'F') {
           Asm("           dw      gtefp");
           opType = 'I';
           AddExternal(currentProc, "gtefp");
           }
         else if (use32Bits) {
           Asm("           dw      gte32");
           AddExternal(currentProc, "gte32");
           }
         else {
           Asm("           dw      gte16");
           AddExternal(currentProc, "gte16");
           }
         break;
    case OP_LTE:
         Asm("           sep     scall               ; Perform less or equal");
         if (opType == 'F') {
           Asm("           dw      ltefp");
           opType = 'I';
           AddExternal(currentProc, "ltefp");
           }
         else if (use32Bits) {
           Asm("           dw      lte32");
           AddExternal(currentProc, "lte32");
           }
         else {
           Asm("           dw      lte16");
           AddExternal(currentProc, "lte16");
           }
         break;
    case OP_EQ :
         Asm("           sep     scall               ; Perform equal");
         if (opType == 'F') {
           Asm("           dw      eqfp");
           AddExternal(currentProc, "eqfp");
           opType = 'I';
           }
         else if (use32Bits) {
           Asm("           dw      eq32");
           AddExternal(currentProc, "eq32");
           }
         else {
           Asm("           dw      eq16");
           AddExternal(currentProc, "eq16");
           }
         break;
    case OP_NE :
         Asm("           sep     scall               ; Perform not equal");
         if (opType == 'F') {
           Asm("           dw      nefp");
           AddExternal(currentProc, "nefp");
           opType = 'I';
           }
         else if (use32Bits) {
           Asm("           dw      ne32");
           AddExternal(currentProc, "ne32");
           }
         else {
           Asm("           dw      ne16");
           AddExternal(currentProc, "ne16");
           }
         break;
    case OP_AND:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point arguments to integer");
           Asm("           dw      ftoi");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           sep     scall");
           Asm("           dw      ftoi");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           sep     scall               ; Perform AND");
         if (use32Bits) {
           Asm("           dw      and32");
           AddExternal(currentProc, "and32");
           }
         else {
           Asm("           dw      and16");
           AddExternal(currentProc, "and16");
           }
         break;
    case OP_OR :
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point arguments to integer");
           Asm("           dw      ftoi");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           sep     scall");
           Asm("           dw      ftoi");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           sep     scall               ; Perform OR");
         if (use32Bits) {
           Asm("           dw      or32");
           AddExternal(currentProc, "or32");
           }
         else {
           Asm("           dw      or16");
           AddExternal(currentProc, "or16");
           }
         break;
    case OP_XOR:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point arguments to integer");
           Asm("           dw      ftoi");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           inc     r7");
           Asm("           sep     scall");
           Asm("           dw      ftoi");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           Asm("           dec     r7");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           sep     scall               ; Perform XOR");
         if (use32Bits) {
           Asm("           dw      xor32");
           AddExternal(currentProc, "xor32");
           }
         else {
           Asm("           dw      xor16");
           AddExternal(currentProc, "xor16");
           }
         break;
    case OP_PEEK:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           inc     r7                  ; Retrieve address for peek");
         Asm("           lda     r7");
         Asm("           plo     rf");
         Asm("           ldn     r7");
         Asm("           phi     rf");
         if (use32Bits) {
           Asm("           inc     r7                  ; Remove high word");
           Asm("           inc     r7");
           }
         Asm("           ldi     0                   ; Result is a byte, so MSB=0");
         Asm("           str     r7");
         Asm("           dec     r7");
         if (use32Bits) {
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_DPEEK:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           inc     r7                  ; Retrieve address for peek");
         Asm("           lda     r7");
         Asm("           plo     rf");
         Asm("           ldn     r7");
         Asm("           phi     rf");
         if (use32Bits) {
           Asm("           inc     r7                  ; Remove high word");
           Asm("           inc     r7");
           Asm("           ldi     0                   ; Result is a word, so MSW=0");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           lda     rf                  ; Result word from memory");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_FLG:
         opType = 'I';
         Asm("           inc     r7                  ; FLG needs no args, so remove dummy");
         Asm("           inc     r7");
         if (use32Bits) {
           Asm("           inc     r7");
           Asm("           inc     r7");
           }
         Asm("           ldi     0                   ; Result is a byte, so MSB=0");
         Asm("           str     r7");
         Asm("           dec     r7");
         if (use32Bits) {
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           sep     scall               ; Read EF flags");
         Asm("           dw      readef");
         Asm("           str     r7");
         Asm("           dec     r7");
         AddExternal(currentProc, "readef");
         break;
    case OP_FRE:
         opType = 'I';
         Asm("           inc     r7                  ; FRE needs no args, so remove dummy");
         Asm("           inc     r7");
         if (use32Bits) {
           Asm("           inc     r7");
           Asm("           inc     r7");
           }
         if (useHeap) {
           if (use32Bits) {
             Asm("           ldi     0                   ; High word is zero");
             Asm("           str     r7");
             Asm("           dec     r7");
             Asm("           str     r7");
             Asm("           dec     r7");
             }
           Asm("           ldi     HEAP_.1             ; Get address of heap");
           Asm("           phi     rf");
           Asm("           ldi     HEAP_.0");
           Asm("           plo     rf");
           Asm("           lda     rf                  ; Retrieve free memory address");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           ldn     rf");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         else {
           if (use32Bits) {
             Asm("           ldi     0                   ; High word is zero");
             Asm("           str     r7");
             Asm("           dec     r7");
             Asm("           str     r7");
             Asm("           dec     r7");
             }
           Asm("           ghi     r7                  ; use expr stack pointer as high");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           glo     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         if (use32Bits) {
           Asm("           ldi     FREE_+2.1             ; Get address of free memory");
           Asm("           phi     rf");
           Asm("           ldi     FREE_+2.0");
           Asm("           plo     rf");
           Asm("           ldi     0                   ; High word is zero");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         else {
           Asm("           ldi     FREE_.1             ; Get address of free memory");
           Asm("           phi     rf");
           Asm("           ldi     FREE_.0");
           Asm("           plo     rf");
           }
         Asm("           lda     rf                  ; Retrieve free memory address");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           sep     scall               ; Perform subtraction");
         if (use32Bits) Asm("           dw      sub32");
           else Asm("           dw      sub16");
         break;
    case OP_INP:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           ldi     0d3h                ; Push SEP R3 onto stack");
         Asm("           stxd");
         Asm("           inc     r7                  ; Retrieve port");
         Asm("           lda     r7");
         if (use32Bits) {
           Asm("           inc     r7                  ; Remove high word");
           Asm("           inc     r7");
           }
         Asm("           ani     7                   ; Keep only bottom 3 bits");
         Asm("           adi     068h                ; convert to INP instruction");
         Asm("           stxd");
         Asm("           glo     r2                  ; Copy stack address to RF");
         Asm("           plo     rf");
         Asm("           ghi     r2");
         Asm("           phi     rf");
         Asm("           inc     rf                  ; RF now points to INP command");
         Asm("           sep     rf                  ; Execute code on stack");
         Asm("           ldi     0                   ; High byte is zero");
         Asm("           str     r7");
         Asm("           dec     r7");
         if (use32Bits) {
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           ldx                         ; Retrieve value from INP");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_ALLOC:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           inc     r7                  ; Get size from expr stack");
         Asm("           lda     r7");
         Asm("           plo     rc");
         Asm("           ldn     r7");
         Asm("           phi     rc");
         if (use32Bits) {
           Asm("           inc     r7                  ; Remove high word");
           Asm("           inc     r7");
           }
         Asm("           sep     scall               ; Call alloc function");
         Asm("           dw      alloc");
         AddExternal(currentProc, "alloc");
         useHeap = -1;
         if (use32Bits) {
           Asm("           ldi     0                   ; Clear high word");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           ghi     rf                  ; Push address to expr stack");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           glo     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_CINT:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         break;
    case OP_CSNG:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
    case OP_SIN:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform sin function");
         Asm("           dw      fpsin");
         AddExternal(currentProc, "fpsin");
         break;
    case OP_COS:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform cos function");
         Asm("           dw      fpcos");
         AddExternal(currentProc, "fpcos");
         break;
    case OP_TAN:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform tan function");
         Asm("           dw      fptan");
           AddExternal(currentProc, "fptan");
         break;
    case OP_LN:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform ln function");
         Asm("           dw      fpln");
         AddExternal(currentProc, "fpln");
         break;
    case OP_EXP:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform exp function");
         Asm("           dw      fpexp");
         AddExternal(currentProc, "fpexp");
         break;
    case OP_SQRT:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform sqrt function");
         Asm("           dw      fpsqrt");
         AddExternal(currentProc, "fpsqrt");
         break;
    case OP_ATAN:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform atan function");
         Asm("           dw      fpatan");
         AddExternal(currentProc, "fpatan");
         break;
    case OP_ACOS:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform acos function");
         Asm("           dw      fpacos");
         AddExternal(currentProc, "fpacos");
         break;
    case OP_ASIN:
         if (opType == 'I') {
           Asm("           sep     scall               ; Convert integer argument to floating-point");
           Asm("           dw      itof");
           AddExternal(currentProc, "itof");
           opType = 'F';
           }
         Asm("           sep     scall               ; Perform asin function");
         Asm("           dw      fpasin");
         AddExternal(currentProc, "fpasin");
         break;
    case OP_POS:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           inc     r7                  ; Retrieve file number");
         Asm("           lda     r7");
         if (use32Bits) {
           Asm("           inc     r7");
           Asm("           inc     r7");
           }
         Asm("           smi     1                   ; subtract 1");
         Asm("           shl                         ; multiply file number by 2");
         Asm("           adi     file1_.0            ; add to file handles");
         Asm("           plo     rf                  ; save in pointer");
         Asm("           ldi     file1_.1            ; get high byte of address");
         Asm("           adci    0                   ; propagate carry");
         Asm("           phi     rf                  ; RF now has file handle");
         Asm("           lda     rf                  ; retrieve FILDES");
         Asm("           phi     rd");
         Asm("           ldn     rf");
         Asm("           plo     rd");
         if (use32Bits) {
           Asm("           lda     rd                  ; get file position");
           Asm("           str     r7                  ; write to expression stack");
           Asm("           dec     r7");
           Asm("           lda     rd");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           lda     rd");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           lda     rd");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         else {
           Asm("           inc     rd                  ; move to lsw");
           Asm("           inc     rd");
           Asm("           lda     rd                  ; get file position");
           Asm("           str     r7                  ; write to expression stack");
           Asm("           dec     r7");
           Asm("           lda     rd");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         break;
    case OP_EOF:
         if (opType == 'F') {
           Asm("           sep     scall               ; Convert floating point argument to integer");
           Asm("           dw      ftoi");
           AddExternal(currentProc, "ftoi");
           opType = 'I';
           }
         Asm("           inc     r7                  ; Retrieve file number");
         Asm("           lda     r7");
         if (use32Bits) {
           Asm("           inc     r7");
           Asm("           inc     r7");
           }
         Asm("           sep     scall               ; check for EOF");
         if (use32Bits) {
           Asm("           dw      eof32");
           Asm("           str     r7                  ; store result");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           AddExternal(currentProc, "eof32");
           }
         else {
           Asm("           dw      eof16");
           Asm("           str     r7                  ; store result");
           Asm("           dec     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           AddExternal(currentProc, "eof16");
           }
         break;
    }
  tokens[numTokens++] = 0;
  tokens[numTokens++] = (opType == 'I') ? OP_NUM : OP_NUMFP;
  return ret;
  }

void add(int op) {
  if (tokens[numTokens-1] >= 0x10) {
    }
  while (numTokens > 4 && (op & 0xf0) <= (tokens[numTokens-3] & 0xf0)) {
    reduce(0);
    }
  tokens[numTokens++] = op;
  }

char* evaluate(char* buffer) {
  int  i;
  int  fp;
  char abuffer[256];
  char term;
  int p;
  char token[64];
  int flag;
  int func;
  int parens;
  FPI fpi;
  dword number;
  parens = 0;
  numTokens = 0;
  flag = 1;
  while (*buffer == ' ') buffer++;
  if (*buffer == '-' && (*(buffer+1) < '0' || *(buffer+1) > '9')) {
    tokens[numTokens++] = 0;
    tokens[numTokens++] = OP_NUM;
    tokens[numTokens++] = OP_SUB;
    buffer++;
    }
  while (*buffer != 0 && flag) {

    while (*buffer == ' ') buffer++;

    func = -1;
    while (func) {
      func = 0;
      while (*buffer == '(') {
        tokens[numTokens++] = OP_OP;
        parens++;
        buffer++;
        func = -1;
        }
      if (strncasecmp(buffer,"peek(",5) == 0) {
         tokens[numTokens++] = OP_PEEK;
         tokens[numTokens++] = OP_OP;
         buffer+=5;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"dpeek(",6) == 0) {
         tokens[numTokens++] = OP_DPEEK;
         tokens[numTokens++] = OP_OP;
         buffer+=6;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"flg(",4) == 0) {
         tokens[numTokens++] = OP_FLG;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"fre(",4) == 0) {
         tokens[numTokens++] = OP_FRE;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"inp(",4) == 0) {
         tokens[numTokens++] = OP_INP;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"abs(",4) == 0) {
         tokens[numTokens++] = OP_ABS;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"rnd(",4) == 0) {
         tokens[numTokens++] = OP_RND;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"sgn(",4) == 0) {
         tokens[numTokens++] = OP_SGN;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"alloc(",6) == 0) {
         tokens[numTokens++] = OP_ALLOC;
         tokens[numTokens++] = OP_OP;
         buffer+=6;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"pos(",4) == 0) {
         tokens[numTokens++] = OP_POS;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"eof(",4) == 0) {
         tokens[numTokens++] = OP_EOF;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (useFp) {
        if (strncasecmp(buffer,"cint(",5) == 0) {
           tokens[numTokens++] = OP_CINT;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"csng(",5) == 0) {
           tokens[numTokens++] = OP_CSNG;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"sin(",4) == 0) {
           tokens[numTokens++] = OP_SIN;
           tokens[numTokens++] = OP_OP;
           buffer+=4;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"cos(",4) == 0) {
           tokens[numTokens++] = OP_COS;
           tokens[numTokens++] = OP_OP;
           buffer+=4;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"tan(",4) == 0) {
           tokens[numTokens++] = OP_TAN;
           tokens[numTokens++] = OP_OP;
           buffer+=4;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"ln(",3) == 0) {
           tokens[numTokens++] = OP_LN;
           tokens[numTokens++] = OP_OP;
           buffer+=3;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"exp(",4) == 0) {
           tokens[numTokens++] = OP_EXP;
           tokens[numTokens++] = OP_OP;
           buffer+=4;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"sqrt(",5) == 0) {
           tokens[numTokens++] = OP_SQRT;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"atan(",5) == 0) {
           tokens[numTokens++] = OP_ATAN;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"asin(",5) == 0) {
           tokens[numTokens++] = OP_ASIN;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        if (strncasecmp(buffer,"acos(",5) == 0) {
           tokens[numTokens++] = OP_ACOS;
           tokens[numTokens++] = OP_OP;
           buffer+=5;
           parens++;
           func = -1;
           }
        }
      }

    term = 0;

    /* ******************************************* */
    /* ***** Process floating-point constant ***** */
    /* ******************************************* */
    buffer = isFloatingPointNumber(buffer, token);
    if (exprErrors > 0) {
      *buffer = 0;
      return buffer;
      }
    if (strlen(token) > 0) {
      if (useFp) {
        fpi.f = atof(token);
        tokens[numTokens++] = 0;
        tokens[numTokens++] = OP_NUMFP;
        sprintf(abuffer,"           ldi     %d                  ; Push floating-point constant onto expr stack",(fpi.i & 0xff000000) >> 24); Asm(abuffer);
        Asm("           sex     r7");
        Asm("           stxd");
        sprintf(abuffer,"           ldi     %d",(fpi.i & 0xff0000) >> 16); Asm(abuffer);
        Asm("           stxd");
        sprintf(abuffer,"           ldi     %d",(fpi.i & 0xff00) >> 8); Asm(abuffer);
        Asm("           stxd");
        sprintf(abuffer,"           ldi     %d",fpi.i & 0xff); Asm(abuffer);
        Asm("           stxd");
        Asm("           sex     r2");
        term = -1;
        }
      else {
        showError("Floating point not allowed in integer mode");
        exprErrors++;
        *buffer = 0;
        return buffer;
        }
      }

    /* ************************************ */
    /* ***** Process integer constant ***** */
    /* ************************************ */
    if (term == 0) {
      buffer = isIntegerNumber(buffer, token);
      if (strlen(token) > 0) {
        number = atoi(token);
        tokens[numTokens++] = 0;
        tokens[numTokens++] = OP_NUM;
        if (use32Bits) {
          sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",(number & 0xff000000) >> 24); Asm(abuffer);
          Asm("           str     r7");
          Asm("           dec     r7");
          sprintf(abuffer,"           ldi     %d",(number & 0xff0000) >> 16); Asm(abuffer);
          Asm("           str     r7");
          Asm("           dec     r7");
          }
        sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",(number & 0xff00) >> 8); Asm(abuffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(abuffer,"           ldi     %d",number & 0xff); Asm(abuffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        term = -1;
        }
      }

    /* ******************************** */
    /* ***** Process hex constant ***** */
    /* ******************************** */
    if (term == 0) {
      if (*buffer == '$' &&
             ((*(buffer+1) >= 'a' && *(buffer+1) <= 'f') ||
              (*(buffer+1) >= 'A' && *(buffer+1) <= 'F') ||
              (*(buffer+1) >= '0' && *(buffer+1) <= '9'))) {
        buffer++;
        number = 0;
        while ((*buffer >= '0' && *buffer <= '9') ||
               (*buffer >= 'a' && *buffer <= 'f') ||
               (*buffer >= 'A' && *buffer <= 'F')) {
          if (*buffer >= '0' && *buffer <= '9') number = (number << 4) + (*buffer - '0');
          if (*buffer >= 'a' && *buffer <= 'f') number = (number << 4) + (*buffer - 'a') + 10;
          if (*buffer >= 'A' && *buffer <= 'F') number = (number << 4) + (*buffer - 'A') + 10;
          buffer++;
          }
        tokens[numTokens++] = 0;
        tokens[numTokens++] = OP_NUM;
        if (use32Bits) {
          sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",(number & 0xff000000) >> 24); Asm(abuffer);
          Asm("           str     r7");
          Asm("           dec     r7");
          sprintf(abuffer,"           ldi     %d",(number & 0xff0000) >> 16); Asm(abuffer);
          Asm("           str     r7");
          Asm("           dec     r7");
          }
        sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",(number & 0xff00) >> 8); Asm(abuffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(abuffer,"           ldi     %d",number & 0xff); Asm(abuffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        term = -1;
        }
      }

    if (term == 0) {
      fp = 0;
      if ((*buffer >= 'a' && *buffer <= 'z') ||
          (*buffer >= 'A' && *buffer <= 'Z')) {
        p = 0;
        while ((*buffer >= 'a' && *buffer <= 'z') ||
               (*buffer >= 'A' && *buffer <= 'Z') ||
               (*buffer >= '0' && *buffer <= '9') ||
                *buffer == '_') {
          token[p++] = *buffer++;
          if (useFp) {
            if (*buffer == '!') {
              fp = -1;
              token[p++] = *buffer++;
              while ((*buffer >= 'a' && *buffer <= 'z') ||
                     (*buffer >= 'A' && *buffer <= 'Z') ||
                     (*buffer >= '0' && *buffer <= '9') ||
                      *buffer == '_') {
                showError("Invalid variable name");
                exprErrors++;
                *buffer = 0;
                return buffer;
                }
              }
            }
          }
        token[p] = 0;
        tokens[numTokens++] = 0;
        if (fp) tokens[numTokens++] = OP_NUMFP;
          else tokens[numTokens++] = OP_NUM;
        number = getVariable(token);
        sprintf(abuffer,"           ldi     v_%s.1              ; Push variable onto expr stack",token); Asm(abuffer);
        Asm("           phi     rf");
        sprintf(abuffer,"           ldi     v_%s.0",token); Asm(abuffer);
        Asm("           plo     rf");
        if (use32Bits) {
          Asm("           sex     r7");
          for (i=0; i<4; i++) {
            Asm("           lda     rf");
            Asm("           stxd");
            }
          Asm("           sex     r2");
          }
        else {
          for (i=0; i<2; i++) {
            Asm("           lda     rf");
            Asm("           str     r7");
            Asm("           dec     r7");
            }
          }
        term = -1;
        }
      }

    if (term == 0) {
      showError("Expression error");
      exprErrors++;
      *buffer = 0;
      return buffer;
      }

    while (*buffer == ' ') buffer++;
    while (*buffer == ')' && parens > 0) {
      parens--;
      while (reduce(0)) ;
      buffer++;
      }
    while (*buffer == ' ') buffer++;

    if (*buffer == '+') { add(OP_ADD); buffer++; }
    else if (*buffer == '-') { add(OP_SUB); buffer++; }
    else if (*buffer == '*') { add(OP_MUL); buffer++; }
    else if (*buffer == '/') { add(OP_DIV); buffer++; }
    else if (*buffer == '%') { add(OP_MOD); buffer++; }
    else if (*buffer == '&') { add(OP_AND); buffer++; }
    else if (*buffer == '|') { add(OP_OR); buffer++; }
    else if (*buffer == '^') { add(OP_XOR); buffer++; }
    else if (*buffer == '<' && *(buffer+1) == '=') { add(OP_LTE); buffer+=2; }
    else if (*buffer == '>' && *(buffer+1) == '=') { add(OP_GTE); buffer+=2; }
    else if (*buffer == '<' && *(buffer+1) == '>') { add(OP_NE); buffer+=2; }
    else if (*buffer == '<') { add(OP_LT); buffer++; }
    else if (*buffer == '>') { add(OP_GT); buffer++; }
    else if (*buffer == '=') { add(OP_EQ); buffer++; }
    else flag = 0;
    }
  while (reduce(-1));
  if (numTokens != 2) {
    showError("Expression error\n");
    exprErrors++;
    *buffer = 0;
    return buffer;
    }
  return buffer;
  }


char* cexpr(char* line, int etype) {
  int   i;
  int   pos;
  int   fp;
  word  num;
  dword num32;
  char  token[128];
  char *temp;
  char  neg;
  char  handled;
  line = trim(line);
  temp = line;
  handled = 0;
  numTokens = 0;
  exprErrors = 0;

  fp = 0;
  /* ************************************************* */
  /* ***** If expression is just a single number ***** */
  /* ***** then set RC=to that number            ***** */
  /* ************************************************* */
  if ((*temp == '-' && *(temp+1) >= '0' && *(temp+1) <= '9') ||
      (*temp >= '0' && *temp <= '9')) {
    neg = 0;
    if (*temp == '-') {
      neg = -1;
      temp++;
      }
    if (use32Bits) {
      num32 = 0;
      while (*temp >= '0' && *temp <= '9') {
        num32 = (num32 * 10) + (*temp - '0');
        temp++;
        }
      if (neg) num32 = (num32 ^0xffffffff) + 1;
      temp=trim(temp);
      if (*temp == ',' || *temp == ';' || *temp == 0 ||
          (*temp >= 'a' && *temp <= 'z') ||
          (*temp >= 'A' && *temp <= 'Z')) {
        sprintf(buffer,"           ldi     %d                  ; Set expression result to constant",(num32 & 0xff000000) >> 24); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(buffer,"           ldi     %d",(num32 & 0xff0000) >> 16); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(buffer,"           ldi     %d",(num32 & 0xff00) >> 8); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(buffer,"           ldi     %d",num32 & 0xff); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        tokens[numTokens++] = 0;
        tokens[numTokens++] = OP_NUM;
        line = temp;
        handled = -1;
        }
      }
    else {
      num = 0;
      while (*temp >= '0' && *temp <= '9') {
        num = (num * 10) + (*temp - '0');
        temp++;
        }
      if (neg) num = (num ^0xffff) + 1;
      temp=trim(temp);
      if (*temp == ',' || *temp == ';' || *temp == 0 ||
          (*temp >= 'a' && *temp <= 'z') ||
          (*temp >= 'A' && *temp <= 'Z')) {
        sprintf(buffer,"           ldi     %d                  ; Set expression result to constant",num/256); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        sprintf(buffer,"           ldi     %d",num%256); Asm(buffer);
        Asm("           str     r7");
        Asm("           dec     r7");
        line = temp;
        tokens[numTokens++] = 0;
        tokens[numTokens++] = OP_NUM;
        handled = -1;
        }
      }
    }

  /* *************************************************** */
  /* ***** If expression is just a single variable ***** */
  /* ***** then retrieve that variable into RC     ***** */
  /* *************************************************** */
  if ((*temp >= 'a' && *temp <= 'z') ||
      (*temp >= 'A' && *temp <= 'Z') ||
      (*temp >= '0' && *temp <= '9') ||
      *temp == '_') {
    pos = 0;
    while ((*temp >= 'a' && *temp <= 'z') ||
           (*temp >= 'A' && *temp <= 'Z') ||
           (*temp >= '0' && *temp <= '9') ||
           *temp == '_') {
      token[pos++] = *temp++;
      if (useFp) {
        if (*temp == '!') {
          fp = -1;
          token[pos++] = *temp++;
          while ((*temp >= 'a' && *temp <= 'z') ||
                 (*temp >= 'A' && *temp <= 'Z') ||
                 (*temp >= '0' && *temp <= '9') ||
                 *temp == '_') {
            showError("Invalid variable name");
            *line = 0;
            return line;
            }
          }
        }
      }
    token[pos] = 0;
    if (*temp == ',' || *temp == ';' || *temp == 0) {
      num = getVariable(token);
      sprintf(buffer,"           ldi     v_%s.1              ; Set expression to variable value",token); Asm(buffer);
      Asm("           phi     rf");
      sprintf(buffer,"           ldi     v_%s.0",token); Asm(buffer);
      Asm("           plo     rf");
      if (use32Bits) {
        for (i=0; i<4; i++) {
          Asm("           lda     rf");
          Asm("           str     r7");
          Asm("           dec     r7");
          }
        }
      else {
        for (i=0; i<2; i++) {
          Asm("           lda     rf");
          Asm("           str     r7");
          Asm("           dec     r7");
          }
        }
      tokens[numTokens++] = 0;
      if (fp) tokens[numTokens++] = OP_NUMFP;
        else tokens[numTokens++] = OP_NUM;
      line = temp;
      handled = -1;
      }
    }

  /* **************************************** */
  /* ***** Otherwise process expression ***** */
  /* **************************************** */
  if (!handled) {
    line = evaluate(line);
    if (exprErrors > 0) {
      *line = 0;
      return line;
      }
    }
  if (numTokens != 2) {
    showError("Expression error");
    *line = 0;
    return line;
    }
  if (tokens[1] != OP_NUM && tokens[1] != OP_NUMFP) {
    showError("Expression error");
    *line = 0;
    return line;
    }
  if (tokens[1] == OP_NUM && etype == 1) {
    Asm("           sep     scall               ; Convert integer to floating point");
    Asm("           dw      itof");
    AddExternal(currentProc, "itof");
    }
  if (tokens[1] == OP_NUMFP && etype == 0) {
    Asm("           sep     scall               ; Convert floating point to integer");
    Asm("           dw      ftoi");
    AddExternal(currentProc, "ftoi");
    }
  return line;
  }

