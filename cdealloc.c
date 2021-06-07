#include "header.h"

char* cdealloc(char* line) {
  word target;
  line = trim(line);
  line = cexpr(line);
  Asm("           inc     r7                  ; Get transfer address");
  Asm("           lda     r7");
  Asm("           plo     rf");
  Asm("           ldn     r7");
  Asm("           phi     rf");
  Asm("           sep     scall               ; Call dealloc routine");
  Asm("           dw      dealloc");
  return line;
  }

