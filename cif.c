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

char* cif(char* line) {
  word addr;
  int  lelse, lendif;
  line = trim(line);
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

  if (*line == 0) {
    lelse = ++autoLabel;
    lendif = ++autoLabel;
    ifs[numIfs][0] = lelse;
    ifs[numIfs][1] = lendif;
    sprintf(buffer,"          lbz   lbl_%d                    ; Jump if test failed",lelse); Asm(buffer);
    numIfs++;
    }

  else {
    findNextLineNumber(lastLineNumber, &addr);
    sprintf(buffer,"          lbz   la_%d                    ; Jump if test failed",autoLine+1); Asm(buffer);
    if (strncasecmp(line,"then",4) == 0) {
      line += 4;
      }
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

