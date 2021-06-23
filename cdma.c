#include "header.h"

char* cdma(char* line) {
  word target;
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

