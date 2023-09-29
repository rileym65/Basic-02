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
    *line = 0;
    return line;
    }
  line++;
  if (*line < '1' || *line > '8') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  fnum = *line - '1';
  line++;
  line = trim(line);
  line = cexpr(line, 0);
  if (exprErrors > 0) return line;
  if (use32Bits) {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          stxd                          ; save on stack for now");
    Asm("          ldn   r7");
    Asm("          stxd");
    Asm("          inc   r7");
    Asm("          inc   r7");
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
    *line = 0;
    return line;
    }
  line++;
  line = cexpr(line, 0);
  if (exprErrors > 0) return line;
  if (use32Bits) {
    Asm("          inc   r7                      ; Retrieve address");
    Asm("          lda   r7");
    Asm("          plo   rc                      ; place into count register");
    Asm("          ldn   r7");
    Asm("          phi   rc");
    Asm("          inc   r7");
    Asm("          inc   r7");
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
  Asm("          sep   scall                   ; Set I/O return variables");
  Asm("          dw    ioresults");
  Asm("          lbdf  $+14                    ; jump on error");
  Asm("          ldi   v_ioresult.1            ; point to i/o result variable");
  Asm("          phi   rf");
  Asm("          ldi   v_ioresult.0");
  Asm("          plo   rf");
  if (use32Bits) {
  Asm("          ldi   0                       ; Clear high word when 32 bits mode");
    Asm("          str   rf");
    Asm("          inc   rf");
    Asm("          str   rf");
    Asm("          inc   rf");
    }
  Asm("          ghi   rc                      ; store count of bytes written");
  Asm("          str   rf");
  Asm("          inc   rf");
  Asm("          glo   rc");
  Asm("          str   rf");

  AddExternal(currentProc, "ioresults");
  AddExternal(currentProc, "v_ioresult");

  while (*line != ':' && *line != 0) line++;
  return line;
  }

