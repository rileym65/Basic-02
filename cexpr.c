#include "header.h"

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
#define OP_NUM    0x00
int     tokens[64];
int     numTokens;

int reduce(char last) {
  int i;
  int arg1,arg2;
  int op;
  int done;
  int flag;
  int ret;
  word addr;
  flag = 0;
  if (numTokens == 0) return 0;
  if (tokens[numTokens-1] != OP_NUM) return 0;
  if (numTokens > 2 && tokens[numTokens-3] >= 0x50) {
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (last) ret = -1;
    }
  else if (numTokens > 2 && tokens[numTokens-3] == OP_OP) {
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (numTokens > 0 && tokens[numTokens-1] >= 0x50) ret = -1;
    if (last) ret = -1;
    }
  else if (numTokens > 4 && tokens[numTokens-3] >= 0x10 &&
                            tokens[numTokens-4] == OP_NUM) {
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
         Asm("           dw      sgn16");
         break;
    case OP_RND:
         Asm("           sep     scall               ; Perform RND()");
         Asm("           dw      rnd16");
         break;
    case OP_ABS:
         Asm("           sep     scall               ; Perform ABS()");
         Asm("           dw      abs16");
         break;
    case OP_MUL:
         Asm("           sep     scall               ; Perform multiplication");
         Asm("           dw      mul16");
         break;
    case OP_DIV:
         Asm("           sep     scall               ; Perform division");
         Asm("           dw      div16");
         break;
    case OP_MOD:
         Asm("           sep     scall               ; Perform modulo");
         Asm("           dw      mod16");
         break;
    case OP_ADD:
         Asm("           sep     scall               ; Perform addition");
         Asm("           dw      add16");
         break;
    case OP_SUB:
         Asm("           sep     scall               ; Perform subtraction");
         Asm("           dw      sub16");
         break;
    case OP_GT :
         Asm("           sep     scall               ; Perform greater than");
         Asm("           dw      gt16");
         break;
    case OP_LT :
         Asm("           sep     scall               ; Perform less than");
         Asm("           dw      lt16");
         break;
    case OP_GTE:
         Asm("           sep     scall               ; Perform greater or equal");
         Asm("           dw      gte16");
         break;
    case OP_LTE:
         Asm("           sep     scall               ; Perform less or equal");
         Asm("           dw      lte16");
         break;
    case OP_EQ :
         Asm("           sep     scall               ; Perform equal");
         Asm("           dw      eq16");
         break;
    case OP_NE :
         Asm("           sep     scall               ; Perform not equal");
         Asm("           dw      ne16");
         break;
    case OP_AND:
         Asm("           sep     scall               ; Perform AND");
         Asm("           dw      and16");
         break;
    case OP_OR :
         Asm("           sep     scall               ; Perform OR");
         Asm("           dw      or16");
         break;
    case OP_XOR:
         Asm("           sep     scall               ; Perform XOR");
         Asm("           dw      xor16");
         break;
    case OP_PEEK:
         Asm("           inc     r7                  ; Retrieve address for peek");
         Asm("           lda     r7");
         Asm("           plo     rf");
         Asm("           ldn     r7");
         Asm("           phi     rf");
         Asm("           ldi     0                   ; Result is a byte, so MSB=0");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_DPEEK:
         Asm("           inc     r7                  ; Retrieve address for peek");
         Asm("           lda     r7");
         Asm("           plo     rf");
         Asm("           ldn     r7");
         Asm("           phi     rf");
         Asm("           lda     rf                  ; Result word from memory");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_FLG:
         Asm("           inc     r7                  ; FLG needs no args, so remove dummy");
         Asm("           inc     r7");
         Asm("           ldi     0                   ; Result is a byte, so MSB=0");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           sep     scall               ; Read EF flags");
         Asm("           dw      readef");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_FRE:
         Asm("           inc     r7                  ; FRE needs no args, so remove dummy");
         Asm("           inc     r7");
         if (useHeap) {
           Asm("           ldi     [HEAP_].1           ; Get address of heap");
           Asm("           phi     rf");
           Asm("           ldi     [HEAP_].0");
           Asm("           plo     rf");
           Asm("           lda     rf                  ; Retrieve free memory address");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           ldn     rf");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         else {
           Asm("           ghi     r7                  ; use expr stack pointer as high");
           Asm("           str     r7");
           Asm("           dec     r7");
           Asm("           glo     r7");
           Asm("           str     r7");
           Asm("           dec     r7");
           }
         Asm("           ldi     [FREE_].1           ; Get address of free memory");
         Asm("           phi     rf");
         Asm("           ldi     [FREE_].0");
         Asm("           plo     rf");
         Asm("           lda     rf                  ; Retrieve free memory address");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           ldn     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           sep     scall               ; Perform subtraction");
         Asm("           dw      sub16");
         break;
    case OP_INP:
         Asm("           ldi     0d3h                ; Push SEP R3 onto stack");
         Asm("           stxd");
         Asm("           inc     r7                  ; Retrieve port");
         Asm("           lda     r7");
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
         Asm("           ldx                         ; Retrieve value from INP");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    case OP_ALLOC:
         Asm("           inc     r7                  ; Get size from expr stack");
         Asm("           lda     r7");
         Asm("           plo     rc");
         Asm("           ldn     r7");
         Asm("           phi     rc");
         Asm("           sep     scall               ; Call alloc function");
         Asm("           dw      alloc");
         Asm("           ghi     rf                  ; Push address to expr stack");
         Asm("           str     r7");
         Asm("           dec     r7");
         Asm("           glo     rf");
         Asm("           str     r7");
         Asm("           dec     r7");
         break;
    }
  tokens[numTokens++] = 0;
  tokens[numTokens++] = OP_NUM;
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
  char abuffer[128];
  int p;
  char token[64];
  int neg;
  int flag;
  int func;
  int parens;
  word number;
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
      }
    if ((*buffer == '-' && *(buffer+1) >= '0' && *(buffer+1) <= '9') |
        (*buffer >= '0' && *buffer <='9')) {
      neg = (*buffer == '-') ? -1 : 0;
      if (*buffer == '-') buffer++;
      number = 0;
      while (*buffer >= '0' && *buffer <= '9') {
        number = number * 10 + (*buffer - '0');
        buffer++;
        }
      if (neg) {
        number = (number^0xffff) + 1;
        }
      tokens[numTokens++] = 0;
      tokens[numTokens++] = OP_NUM;
      sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",number/256); Asm(abuffer);
      Asm("           str     r7");
      Asm("           dec     r7");
      sprintf(abuffer,"           ldi     %d",number%256); Asm(abuffer);
      Asm("           str     r7");
      Asm("           dec     r7");
      }

    else if (*buffer == '$' &&
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
      sprintf(abuffer,"           ldi     %d                  ; Push constant onto expr stack",number/256); Asm(abuffer);
      Asm("           str     r7");
      Asm("           dec     r7");
      sprintf(abuffer,"           ldi     %d",number%256); Asm(abuffer);
      Asm("           str     r7");
      Asm("           dec     r7");
      }

    else if ((*buffer >= 'a' && *buffer <= 'z') ||
             (*buffer >= 'A' && *buffer <= 'Z')) {
      p = 0;
      while ((*buffer >= 'a' && *buffer <= 'z') ||
             (*buffer >= 'A' && *buffer <= 'Z') ||
             (*buffer >= '0' && *buffer <= '9') ||
              *buffer == '_') {
        token[p++] = *buffer++;
        }
      token[p] = 0;
      tokens[numTokens++] = 0;
      tokens[numTokens++] = OP_NUM;
      number = getVariable(token);
      sprintf(abuffer,"           ldi     [%s].1              ; Push constant onto expr stack",token); Asm(abuffer);
      Asm("           phi     rf");
      sprintf(abuffer,"           ldi     [%s].0",token); Asm(abuffer);
      Asm("           plo     rf");
      Asm("           lda     rf");
      Asm("           str     r7");
      Asm("           dec     r7");
      Asm("           ldn     rf");
      Asm("           str     r7");
      Asm("           dec     r7");
      }
    else {
      printf("Expression error: %s\n",buffer);
      return 0;
      }

    while (*buffer == ' ') buffer++;
    while (*buffer == ')' && parens > 0) {
      parens--;
      while (reduce(0)) ;
      buffer++;
      }

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
  if (numTokens != 2) printf("Expression error\n");
  return buffer;
  }


char* cexpr(char* line) {
  int   pos;
  word  num;
  char  token[128];
  char *temp;
  char  neg;
  line = trim(line);
  temp = line;

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
      return temp;
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
      }
    token[pos] = 0;
    if (*temp == ',' || *temp == ';' || *temp == 0) {
      num = getVariable(token);
      sprintf(buffer,"           ldi     [%s].1              ; Set expression to variable value",token); Asm(buffer);
      Asm("           phi     rf");
      sprintf(buffer,"           ldi     [%s].0",token); Asm(buffer);
      Asm("           plo     rf");
      Asm("           lda     rf");
      Asm("           str     r7");
      Asm("           dec     r7");
      Asm("           ldn     rf");
      Asm("           str     r7");
      Asm("           dec     r7");
      return temp;
      }
    }

  /* **************************************** */
  /* ***** Otherwise process expression ***** */
  /* **************************************** */
  return evaluate(line);
  }

