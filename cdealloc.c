#include "header.h"

char* cdealloc(char* line) {
  word target;
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

