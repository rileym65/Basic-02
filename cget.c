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

char* cget(char* line) {
  byte fnum;
  int i;
  char token[256];
  line = trim(line);
  if (*line != '#') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  if (*line < '1' || *line > '8') {
    showError("Syntax error");
    exit(1);
    }
  fnum = *line - '1';
  line++;
  line = trim(line);
  sprintf(buffer,"          ldi   (file1_+%d*2).0         ; Point to file handle",fnum % 256);
  Asm(buffer);
  Asm("          plo   rf");
  sprintf(buffer,"          ldi   (file1_+%d*2).1",fnum / 256);
  Asm(buffer);
  Asm("          phi   rf");
  Asm("          lda   rf                      ; Retrieve FILDES");
  Asm("          phi   rd");
  Asm("          lda   rf");
  Asm("          plo   rd");

  while (*line != ':' && *line != 0) {
    line=trim(line);
    i = 0;
    while (*line != 0 && *line > ' ' && *line != ',' && *line != ':') {
      token[i++] = *line++;
      }
    token[i] = 0;
    i = getVariable(token);
    sprintf(buffer,"          ldi   v_%s.1                    ; get address of variable data",token);
    Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   v_%s.0",token);
    Asm(buffer);
    Asm("          plo   rf");
    Asm("          ldi   0                       ; set high byte of count to zero");
    Asm("          phi   rc");
    if (useFp || use32Bits) {
      Asm("          ldi   4                       ; set low byte of count to 4");
      Asm("          plo   rc");
      }
    else {
      Asm("          ldi   2                       ; set low byte of count to 2");
      Asm("          plo   rc");
      }
    Asm("          sep   scall                   ; Call Elf/OS to read value");
    Asm("          dw    0309h");
    line=trim(line);
    if (*line == ',') {
      line++;
      line = trim(line);
      }
    }
  return line;
  }

