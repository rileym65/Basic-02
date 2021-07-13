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

char* cout(char* line) {
  int  pos;
  word addr;
  line = cexpr(line, 0);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          ldi   0d3h                    ; Need a SEP R3 command");
  Asm("          stxd                          ; Place on stack");
  Asm("          inc   r7                      ; Get port");
  Asm("          lda   r7");
  Asm("          ani   7                       ; Keep only bottom 3 bits");
  Asm("          ori   060h                    ; Convert to OUT command");
  Asm("          stxd                          ; Place on stack");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  line = cexpr(line, 0);
  Asm("          irx                           ; Recover OUT command");
  Asm("          ldx");
  Asm("          plo   re                      ; Set aside for a moment");
  Asm("          inc   r7                      ; Write out value to stack");
  Asm("          lda   r7");
  Asm("          stxd");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  Asm("          glo   re                      ; Recover OUT command");
  Asm("          str   r2                      ; Place back on stack");
  Asm("          sep   r2                      ; Execute code on stack");
  Asm("          dec   r2                      ; Put stack pointer back where it belongs");
  return line;
  }

