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

char* cpos(char* line) {
  byte fnum;
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
  line = cexpr(line, 0);
  if (use32Bits) {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          plo   rc");
    Asm("          lda   r7");
    Asm("          phi   rc");
    Asm("          lda   r7");
    Asm("          plo   r8");
    Asm("          ldn   r7");
    Asm("          phi   r8");
    Asm("          ghi   r7                      ; save R7");
    Asm("          stxd");
    Asm("          glo   r7");
    Asm("          stxd");
    Asm("          glo   rc                      ; transfer low word to R7");
    Asm("          plo   r7");
    Asm("          ghi   rc");
    Asm("          phi   r7");
    }
  else {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          plo   rc");
    Asm("          ldn   r7");
    Asm("          phi   rc");
    Asm("          ghi   r7                      ; save R7");
    Asm("          stxd");
    Asm("          glo   r7");
    Asm("          stxd");
    Asm("          glo   rc                      ; transfer low word to R7");
    Asm("          plo   r7");
    Asm("          ghi   rc");
    Asm("          phi   r7");
    Asm("          ldi   0                       ; clear high word");
    Asm("          plo   r8");
    Asm("          phi   r8");
    }
  Asm("          ldi   0                       ; Seek from beginning");
  Asm("          plo   rc");
  Asm("          phi   rc");
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
  Asm("          sep   scall                   ; Call Elf/OS to set file position");
  Asm("          dw    030fh");
  Asm("          irx                           ; recover R7");
  Asm("          ldxa");
  Asm("          plo   r7");
  Asm("          ldx");
  Asm("          phi   r7");
  while (*line != ':' && *line != 0) line++;
  return line;
  }

