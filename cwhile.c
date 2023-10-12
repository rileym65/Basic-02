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

char* cwhile(char* line) {
  word addr;
  line = trim(line);
  whiles[numWhiles][0] = ++autoLabel;
  whiles[numWhiles][1] = ++autoLabel;
  sprintf(buffer,"lbl_%d:",whiles[numWhiles][0]); Asm(buffer);
  line = cexpr(line, 0);
  if (exprErrors > 0) return line;
  line = trim(line);
  Asm("          sex   r7                      ; Point X to expr stack");
  Asm("          irx                           ; Move to lsb of result");
  Asm("          ldxa                          ; retrieve it");
  Asm("          or                            ; combine with byte 2");
  if (use32Bits) {
    Asm("          irx                           ; move to byte 3");
    Asm("          or                            ; combine");
    Asm("          irx                           ; move to byte 4");
    Asm("          or                            ; and combine");
    }
  Asm("          sex   r2                      ; Point X to system stack");
  findNextLineNumber(lastLineNumber, &addr);
  sprintf(buffer,"          lbz   lbl_%d                    ; Jump if test failed",whiles[numWhiles][1]); Asm(buffer);
  numWhiles++;
  line = trim(line);
  return line;
  }

