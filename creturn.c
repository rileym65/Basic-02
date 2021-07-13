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

char* creturn(char* line) {
  word target;
  word lineno;
  line = trim(line);
  if (*line >= '0' && *line <= '9') {
    line = getNumber(line, &lineno);
    if (lineno == 0) {
      showError("Invalid line number");
      exit(1);
      }
    if (findLine(lineno, &target) != 0) {
      showError("Line number not found");
      exit(1);
      }
    sprintf(buffer,"          ldi   %d                      ; Set line number for return", target / 256);
    Asm(buffer);
    Asm("          phi   r6");
    sprintf(buffer,"          ldi   %d", target % 256);
    Asm(buffer);
    Asm("          plo   r6");
    }
  Asm("          sep   sret                    ; Return");
  return line;
  }

