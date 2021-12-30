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

char* cchdir(char* line) {
  line = trim(line);
  if (*line != '"') {
    showError("Syntax error");
    *line = 0;
    return;
    }
  line++;
  Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
  Asm("          phi   rf");
  Asm("          ldi   iobuffer.0");
  Asm("          plo   rf");
  while (*line != 0 && *line != '"') {
    sprintf(buffer,"          ldi   0%02xh                    ; get next character",*line++);
    Asm(buffer);
    Asm("          str   rf                      ; write to i/o buffer");
    Asm("          inc   rf                      ; point to next position");
    }
  Asm("          ldi   0                       ; need terminator");
  Asm("          str   rf                      ; write to i/o buffer");
  if (*line != '"') {
    showError("Syntax error");
    *line = 0;
    return;
    }
  line++;
  line = trim(line);
  Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
  Asm("          phi   rf");
  Asm("          ldi   iobuffer.0");
  Asm("          plo   rf");
  Asm("          sep   scall                   ; call Elf/OS to change directory");
  Asm("          dw    0324h");
  while (*line != 0 && *line != ':') line++;
  return line;
  }

