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

char* cdma(char* line) {
  line = trim(line);
  line = cexpr(line, 0);
  Asm("          inc   r7                      ; Set R0 to address");
  Asm("          lda   r7");
  Asm("          plo   r0");
  Asm("          ldn   r7");
  Asm("          phi   r0");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word from stack");
    Asm("          inc   r7");
    }
  return line;
  }

