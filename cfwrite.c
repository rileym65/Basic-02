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

char* cfwrite(char* line) {
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
    Asm("          inc   r7");
    Asm("          inc   r7");
    Asm("          lda   r7");
    Asm("          stxd                          ; save on stack for now");
    Asm("          ldn   r7");
    Asm("          stxd");
    }
  else {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          stxd                          ; save on stack for now");
    Asm("          ldn   r7");
    Asm("          stxd");
    }
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  line = cexpr(line, 0);
  if (use32Bits) {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          inc   r7");
    Asm("          inc   r7");
    Asm("          lda   r7");
    Asm("          plo   rc                      ; place into count register");
    Asm("          ldn   r7");
    Asm("          phi   rc");
    }
  else {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          plo   rc                      ; place into count register");
    Asm("          ldn   r7");
    Asm("          phi   rc");
    }
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
  Asm("          irx                           ; recover address");
  Asm("          ldxa");
  Asm("          phi   rf");
  Asm("          ldx");
  Asm("          plo   rf");
  Asm("          sep   scall                   ; Call Elf/OS to write data");
  Asm("          dw    030ch");
  while (*line != ':' && *line != 0) line++;
  return line;
  }

