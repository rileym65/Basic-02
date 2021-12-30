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

char* cclose(char* line) {
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
  Asm("          sep   scall                   ; Call Elf/OS to close the file");
  Asm("          dw    0312h");
  Asm("          sep   scall                   ; Set I/O return variables");
  Asm("          dw    ioresults");
  sprintf(buffer,"          ldi   (file1_+%d*2).0         ; Point to file handle",fnum % 256);
  Asm(buffer);
  Asm("          plo   rd");
  sprintf(buffer,"          ldi   (file1_+%d*2).1",fnum / 256);
  Asm(buffer);
  Asm("          phi   rd");
  Asm("          lda   rd                      ; Retrieve FILDES");
  Asm("          phi   rf");
  Asm("          lda   rd");
  Asm("          plo   rf");
  Asm("          sep   scall                   ; deallocate memory used by file");
  Asm("          dw    dealloc");

  while (*line != 0 && *line != ':') line++;
  return line;
  }

