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

// On stack:  count stepValue varAddr execAddr  scall

char* cfor(char* line) {
  int  pos;
  word vaddr;
  word addr;
  word value;
  dword start;
  dword end;
  dword step;
  dword loops;
  char quick;
  char varname[256];
  line = trim(line);
  quick = 0;
  if (match(line,"A=#A#A#")) {
    if (strcasecmp(matches[3],"to") == 0 && strcasecmp(matches[5],"step") == 0) {
      vaddr = getVariable(matches[0]);
      start = atoi(matches[2]);
      end = atoi(matches[4]);
      step = atoi(matches[6]);
      loops = (end - start) / step;
      quick = -1;
      }
    }
  if (match(line,"A=#A#")) {
    if (strcasecmp(matches[3],"to") == 0) {
      vaddr = getVariable(matches[0]);
      start = atoi(matches[2]);
      end = atoi(matches[4]);
      step = 1;
      loops = (end - start) / step;
      quick = -1;
      }
    }

  if (quick) {
    sprintf(buffer,"          ldi   [%s].1                  ; Get variable address",matches[0]); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
    Asm("          plo   rf");
    if (use32Bits) {
      sprintf(buffer,"          ldi   %d                      ; Write start to variable",(start & 0xff000000) >> 24); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      sprintf(buffer,"          ldi   %d                      ; Write start to variable",(start & 0xff0000) >> 16); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      }
    sprintf(buffer,"          ldi   %d                      ; Write start to variable",(start & 0xff00) >> 8); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   %d",start & 0xff); Asm(buffer);
    Asm("          str   rf");

    if (use32Bits) {
      sprintf(buffer,"          ldi   %d                      ; Write end value to stack",(loops & 0xff000000) >> 24); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d                      ; Write end value to stack",(loops & 0xff0000) >> 16); Asm(buffer);
      Asm("          stxd");
      }
    sprintf(buffer,"          ldi   %d                      ; Write end value to stack",(loops & 0xff00) >> 8); Asm(buffer);
    Asm("          stxd");
    sprintf(buffer,"          ldi   %d",loops & 0xff); Asm(buffer);
    Asm("          stxd");

    if (use32Bits) {
      sprintf(buffer,"          ldi   %d                      ; Write step value to stack",(step & 0xff000000) >> 24); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d                      ; Write step value to stack",(step & 0xff0000) >> 16); Asm(buffer);
      Asm("          stxd");
      }
    sprintf(buffer,"          ldi   %d                      ; Write step value to stack",(step & 0xff00) >> 8); Asm(buffer);
    Asm("          stxd");
    sprintf(buffer,"          ldi   %d",step & 0xff); Asm(buffer);
    Asm("          stxd");

    sprintf(buffer,"          ldi   [%s].1                  ; Write variable address to stack",matches[0]); Asm(buffer);
    Asm("          stxd");
    sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
    Asm("          stxd");

    addr = address + 6;
    Asm("          ldi   $+6.1                   ; Write execution address to stack");
    Asm("          stxd");
    Asm("          ldi   $+3.0");
    Asm("          stxd");
    while (*line != ':' && *line != 0) line++;
    return line;
    }



  if (!(*line >= 'a' && *line <= 'z') && !(*line >= 'A' && *line <= 'Z')) {
    showError("Invalid variable name");
    exit(1);
    }
  pos = 0;
  while ((*line >= 'a' && *line <= 'z') ||
         (*line >= 'A' && *line <= 'Z') ||
         (*line >= '0' && *line <= '9') ||
         *line == '_') {
    varname[pos++] = *line++;
    }
  varname[pos] = 0;
  line = trim(line);
  if (*line != '=') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  line = trim(line);
  line = cexpr(line, 0);
  vaddr = getVariable(varname);

  if (use32Bits) {
    sprintf(buffer,"          ldi   [%s]+3.1                ; Get variable address",varname); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s]+3.0",varname); Asm(buffer);
    Asm("          plo   rf");
    }
  else {
    sprintf(buffer,"          ldi   [%s]+1.1                ; Get variable address",varname); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s]+1.0",varname); Asm(buffer);
    Asm("          plo   rf");
    }
  Asm("          inc   r7                      ; Store start value into variable");
  Asm("          lda   r7");
  Asm("          str   rf");
  Asm("          dec   rf");
  if (use32Bits) {
    Asm("          lda   r7");
    Asm("          str   rf");
    Asm("          dec   rf");
    Asm("          lda   r7");
    Asm("          str   rf");
    Asm("          dec   rf");
    }
  Asm("          ldn   r7");
  Asm("          str   rf");
  Asm("          dec   r7                      ; keep start on expression stack");
  Asm("          dec   r7");
  if (use32Bits) {
    Asm("          dec   r7");
    Asm("          dec   r7");
    }

  if (strncasecmp(line,"to",2) != 0) {
    showError("Syntax error");
    exit(1);
    }
  line += 2;
  line = trim(line);
  line = cexpr(line, 0);
  line = trim(line);
  if (use32Bits) {
    Asm("          sep   scall                   ; subtract end from start");
    Asm("          dw    sub32");
    Asm("          sep   scall                   ; get absolute value");
    Asm("          dw    abs32");
    }
  else {
    Asm("          sep   scall                   ; subtract end from start");
    Asm("          dw    sub16");
    Asm("          sep   scall                   ; get absolute value");
    Asm("          dw    abs16");
    }

  if (*line == ':' || *line == 0) {
    if (use32Bits) {
      Asm("          inc   r7                      ; Point to loops msb");
      Asm("          inc   r7");
      Asm("          inc   r7");
      Asm("          inc   r7");
      Asm("          ldn   r7                      ; Write loops to stack");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          inc   r7                      ; Remove loops from expr stack");
      Asm("          inc   r7");
      Asm("          inc   r7");
      }
    else {
      Asm("          inc   r7                      ; Get loops value");
      Asm("          lda   r7");
      Asm("          plo   re");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          glo   re");
      Asm("          stxd");
      }
    Asm("          ldi   0                       ; No step, so increment is 1");
    Asm("          stxd");
    if (use32Bits) {
      Asm("          stxd");
      Asm("          stxd");
      }
    Asm("          ldi   1");
    Asm("          stxd");
    }
  else if (strncasecmp(line,"step",4) == 0) {
    line += 4;
    line = trim(line);
    line = cexpr(line, 0);
    line = trim(line);
    if (*line != ':' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    Asm("          stxd                          ; save room for loop count");
    Asm("          stxd");
    if (use32Bits) {
      Asm("          stxd");
      Asm("          stxd");
      Asm("          inc   r7                      ; Point to loops msb");
      Asm("          inc   r7");
      Asm("          inc   r7");
      Asm("          inc   r7");
      Asm("          ldn   r7                      ; Write loops to stack");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          dec   r7");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          dec   r7                      ; keep step on expression stack");
      Asm("          sep   scall                   ; Divide loops by step");
      Asm("          dw    div32");
      Asm("          inc   r7                      ; Point to calculated loops");
      Asm("          glo   r2                      ; need to point to loops on stack");
      Asm("          adi   5");
      Asm("          plo   ra");
      Asm("          ghi   r2");
      Asm("          adci  0");
      Asm("          phi   ra");
      Asm("          lda   r7                      ; move loops to stack");
      Asm("          str   ra");
      Asm("          inc   ra");
      Asm("          lda   r7");
      Asm("          str   ra");
      Asm("          inc   ra");
      Asm("          lda   r7");
      Asm("          str   ra");
      Asm("          inc   ra");
      Asm("          ldn   r7");
      Asm("          str   ra");
      }
    else {
      Asm("          inc   r7                      ; Store increment onto stack");
      Asm("          lda   r7");
      Asm("          plo   re");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          glo   re");
      Asm("          stxd");
      Asm("          dec   r7                      ; keep step on expression stack");
      Asm("          dec   r7");
      Asm("          sep   scall                   ; Divide loops by step");
      Asm("          dw    div16");
      Asm("          inc   r2                      ; point back to loops");
      Asm("          inc   r2");
      Asm("          inc   r2");
      Asm("          inc   r2");
      Asm("          inc   r7                      ; Get loops value");
      Asm("          lda   r7");
      Asm("          plo   re");
      Asm("          ldn   r7");
      Asm("          stxd");
      Asm("          glo   re");
      Asm("          stxd");
      Asm("          dec   r2                      ; move stack below step");
      Asm("          dec   r2");
      }


    }
  else {
    showError("Syntax error");
    exit(1);
    }

  addr = address + 12;

  sprintf(buffer,"          ldi   [%s].1                  ; Write variable address to stack",varname); Asm(buffer);
  Asm("          stxd");
  sprintf(buffer,"          ldi   [%s].0",varname); Asm(buffer);
  Asm("          stxd");
  addr = address + 6;
  Asm("          ldi   $+6.1                   ; Write execution address to stack");
  Asm("          stxd");
  Asm("          ldi   $+3.0");
  Asm("          stxd");

  return line;
  }

