#include "header.h"

char* cdma(char* line) {
  word target;
  line = trim(line);
  line = cexpr(line);
  Asm("          glo   rc                      ; Set R0 to address");
  Asm("          plo   r0");
  Asm("          ghi   rc");
  Asm("          phi   r0");
  return line;
  }

