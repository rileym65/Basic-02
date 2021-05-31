#include "header.h"

char* cpoke(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  output(GHI+RC);
  output(STXD);
  output(GLO+RC);
  output(STXD);
  line = cexpr(line);
  output(IRX);
  output(LDXA);
  output(PLO+RF);
  output(LDX);
  output(PHI+RF);
  output(GLO+RC);
  output(STR+RF);
  return line;
  }

