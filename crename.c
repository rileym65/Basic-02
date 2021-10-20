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

char* crename(char* line) {
  char mode;
  byte fnum;
  line = trim(line);
  if (*line != '"') {
    showError("Syntax error");
    exit(1);
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
  Asm("          inc   rf                      ; point to next position");
  Asm("          ghi   rf                      ; copy address to RC");
  Asm("          phi   rc");
  Asm("          glo   rf");
  Asm("          plo   rc");
  if (*line != '"') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  line = trim(line);
  if (strncasecmp(line, "to", 2) != 0) {
    showError("Syntax error");
    exit(1);
    }
  line += 3;
  line = trim(line);
  if (*line != '"') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  while (*line != 0 && *line != '"') {
    sprintf(buffer,"          ldi   0%02xh                    ; get next character",*line++);
    Asm(buffer);
    Asm("          str   rf                      ; write to i/o buffer");
    Asm("          inc   rf                      ; point to next position");
    }
  Asm("          ldi   0                       ; need terminator");
  Asm("          str   rf                      ; write to i/o buffer");
  Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
  Asm("          phi   rf");
  Asm("          ldi   iobuffer.0");
  Asm("          plo   rf");
  Asm("          sep   scall                   ; call Elf/OS to rename file");
  Asm("          dw    031bh");
  while (*line != 0 && *line != ':') line++;
  return line;
  }

