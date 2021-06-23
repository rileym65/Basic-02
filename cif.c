#include "header.h"

char* cif(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line, 0);
  line = trim(line);
  Asm("          sex   r7                      ; Point X to expr stack");
  Asm("          irx                           ; Move to lsb of result");
  Asm("          ldxa                          ; retrieve it");
  Asm("          or                            ; combine with byte 2");
  if (use32Bits) {
    Asm("          irx                           ; move to byte 3");
    Asm("          or                            ; combine");
    Asm("          irx                           ; move to byte 4");
    Asm("          or                            ; and combine");
    }
  Asm("          sex   r2                      ; Point X to system stack");
  findNextLineNumber(lastLineNumber, &addr);
  sprintf(buffer,"          lbz   <%d>                    ; Jump if test failed",addr); Asm(buffer);
  if (strncasecmp(line,"then",4) == 0) {
    line += 4;
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

