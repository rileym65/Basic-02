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

char* cintr(char* line) {
  word target;
  line = trim(line);
  line = getNumber(line, &target);
  if (target == 0) {
    showError("Invalid line number for intr");
    *line = 0;
    return line;
    }
  if (findLine(target, &target) != 0) {
    showError("Line number not found");
    *line = 0;
    return line;
    }
  Asm("          ldi   [INTR_].1               ; Point to interrupt line");
  Asm("          phi   rf");
  Asm("          ldi   [INTR_].0");
  Asm("          plo   rf");
  sprintf(buffer,"          ldi   0%xh                     ; Set to specified line",target/256); Asm(buffer);
  Asm("          str   rf");
  Asm("          inc   rf");
  sprintf(buffer,"          ldi   0%xh",target%256); Asm(buffer);
  Asm("          str   rf");
  return line;
  }

