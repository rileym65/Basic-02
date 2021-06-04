#include "header.h"

char* ccls(char* line) {
  line = trim(line);
  if (*line != ':' && *line != 0) {
    showError("Syntax error");
    exit(1);
    }
  Asm("          sep   scall                   ; Display message");
  Asm("          dw    f_inmsg");
  Asm("          db    27,'[2J',0");
  return line;
  }

