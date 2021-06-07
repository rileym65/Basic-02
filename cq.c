#include "header.h"

char* cq(char* line) {
  word addr;
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
  line = cexpr(line);
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

