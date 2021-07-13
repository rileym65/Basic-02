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

char* cdpoke(char* line) {
  int  pos;
  word addr;
  line = cexpr(line, 0);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          inc   r7                      ; Get poke address");
  Asm("          lda   r7");
  Asm("          stxd                          ; Store for now");
  Asm("          ldn   r7");
  Asm("          stxd");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  line = cexpr(line, 0);
  Asm("          irx                           ; Recover poke address");
  Asm("          ldxa");
  Asm("          phi   rf");
  Asm("          ldx");
  Asm("          plo   rf");
  Asm("          inc   rf                      ; Point to LSB");
  Asm("          inc   r7");
  Asm("          lda   r7                      ; Get low byte of poke value");
  Asm("          str   rf                      ; And write it to memory");
  Asm("          dec   rf");
  Asm("          ldn   r7                      ; Get high byte of poke value");
  Asm("          str   rf                      ; And write it to memory");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  return line;
  }

