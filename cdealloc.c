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

char* cdealloc(char* line) {
  line = trim(line);
  line = cexpr(line, 0);
  Asm("           inc     r7                  ; Get transfer address");
  Asm("           lda     r7");
  Asm("           plo     rf");
  Asm("           ldn     r7");
  Asm("           phi     rf");
  if (use32Bits) {
    Asm("           inc     r7                  ; Remove high word from stack");
    Asm("           inc     r7");
    }
  Asm("           sep     scall               ; Call dealloc routine");
  Asm("           dw      dealloc");
  return line;
  }

