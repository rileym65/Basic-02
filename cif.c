#include "header.h"

char* cif(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  Asm("          inc   r7                      ; Check lsb of result");
  Asm("          lda   r7");
  Asm("          lbnz  $+7                     ; Jump if successful");
  if (findNextLine(lastLineNumber, &addr) != 0) {
    showError("Line number not found");
    exit(1);
    }
  findNextLineNumber(lastLineNumber, &addr);
  Asm("          ldn   r7                      ; Check high result of compare");
  sprintf(buffer,"          lbz   <%d>                    ; Jump if successful",addr); Asm(buffer);
  if (strncasecmp(line,"then",4) == 0) {
    line += 4;
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

