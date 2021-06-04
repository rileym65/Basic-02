#include "header.h"

char* cdealloc(char* line) {
  word target;
  line = trim(line);
  line = cexpr(line);
  Asm("           glo     rc                  ; Transfer address");
  Asm("           plo     rf");
  Asm("           ghi     rc");
  Asm("           phi     rf");
  Asm("           sep     scall               ; Call dealloc routine");
  Asm("           dw      dealloc");
  return line;
  }

