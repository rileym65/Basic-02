#include "header.h"

char* cgosub(char* line) {
  word target;
  word lineno;
  line = trim(line);
  line = getNumber(line, &lineno);
  if (lineno == 0) {
    showError("Invalid line number for gosub");
    exit(1);
    }
  if (findLine(lineno, &target) != 0) {
    showError("Line number not found");
    exit(1);
    }
  Asm("          sep   scall                   ; Call subroutine");
  sprintf(buffer,"          dw    <%d>",lineno); Asm(buffer);
  return line;
  }

