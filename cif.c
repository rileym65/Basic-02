#include "header.h"

char* cif(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  Asm("          glo   rc                      ; Check result of compare");
  Asm("          lbnz  $+7                     ; Jump if successful");
  if (findNextLine(lastLineNumber, &addr) != 0) {
    showError("Line number not found");
    exit(1);
    }
  findNextLineNumber(lastLineNumber, &addr);
  Asm("          ghi   rc                      ; Check high result of compare");
  sprintf(buffer,"          lbz   <%d>                    ; Jump if successful",addr); Asm(buffer);
  if (strncasecmp(line,"then",4) == 0) {
    line += 4;
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

