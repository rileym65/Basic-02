#include "header.h"

char* cif(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  output(GLO+RC);
  addr = address + 7;
  output(LBNZ); output(addr/256); output(addr%256);
  if (findNextLine(lastLineNumber, &addr) != 0) {
    showError("Line number not found");
    exit(1);
    }
  output(GHI+RC);
  addr = address + 6;
  output(LBZ); output(addr/256); output(addr%256);
  if (strncasecmp(line,"then",4) == 0) {
    line += 4;
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

