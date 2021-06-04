#include "header.h"

char* cgoto(char* line) {
  word target;
  word lineno;
  line = trim(line);
  line = getNumber(line, &lineno);
  if (lineno == 0) {
    showError("Invalid line number for goto");
    exit(1);
    }
  if (findLine(lineno, &target) != 0) {
    showError("Line number not found");
    exit(1);
    }
  sprintf(buffer,"          lbr   <%d>                    ; Jump",lineno); Asm(buffer);
  return line;
  }

