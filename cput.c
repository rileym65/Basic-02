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

char* cput(char* line) {
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
    Asm("          ghi   rd                      ; save FILDES");
    Asm("          stxd");
    Asm("          glo   rd");
    Asm("          stxd");
    line = cexpr(line, 2);
    if (exprErrors > 0) return line;
    Asm("          inc   r7                      ; Point to expression result");
    Asm("          ldi   0                       ; set high byte of count to zero");
    Asm("          phi   rc");
    if (useFp || use32Bits) {
      Asm("          ldi   4                       ; set low byte of count to 4");
      Asm("          plo   rc");
      Asm("          ldi   (iobuffer+3).1          ; point to i/o buffer");
      Asm("          phi   rf");
      Asm("          ldi   (iobuffer+3).0");
      Asm("          plo   rf");
      Asm("          lda   r7                      ; and remove expression from stack");
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          lda   r7");
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          lda   r7");
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   r7");
      Asm("          str   rf");
      }
    else {
      Asm("          ldi   2                       ; set low byte of count to 2");
      Asm("          plo   rc");
      Asm("          ldi   (iobuffer+1).1          ; point to i/o buffer");
      Asm("          phi   rf");
      Asm("          ldi   (iobuffer+1).0");
      Asm("          plo   rf");
      Asm("          lda   r7                      ; and remove expression from stack");
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   r7");
      Asm("          str   rf");
      }
    Asm("          irx                           ; Retrieve FILDES");
    Asm("          ldxa");
    Asm("          plo   rd");
    Asm("          ldx");
    Asm("          phi   rd");
    Asm("          sep   scall                   ; Call Elf/OS to write value");
    Asm("          dw    030ch");
    line=trim(line);
    if (*line == ',') {
      line++;
      line = trim(line);
      }
    }
  Asm("          sep   scall                   ; Set I/O return variables");
  Asm("          dw    ioresults");
  AddExternal(currentProc, "ioresults");
  return line;
  }

