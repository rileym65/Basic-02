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

char* cq(char* line) {
  line = trim(line);
  if (match(line,"#")) {
    if (atoi(line) > 0) {
      Asm("          seq                           ; Turn on Q");
      }
    else {
      Asm("          req                           ; Turn off Q");
      }
    while (*line != ':' && *line != 0) line++;
    return line;
    }
  line = cexpr(line, 0);
  if (exprErrors > 0) return line;
  Asm("          inc   r7                      ; Recover computed value");
  Asm("          lda   r7");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  Asm("          lbz   $+5                     ; Jump if non zero");
  Asm("          req                           ; Turn off Q");
  Asm("          skp                           ; Skip past seq");
  Asm("          seq                           ; Turn on Q");
  return line;
  }

