#include "header.h"

char* cout(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  output(LDI); output(SEP+R3);
  output(STXD);
  output(LDI); output(0x07);
  output(STR+R2);
  output(GLO+RC);
  output(AND);
  output(STR+R2);
  output(LDI); output(0x60);
  output(OR);
  output(STXD);
  line = cexpr(line);
  output(IRX);
  output(LDX);
  output(PLO+RE);
  output(GLO+RC);
  output(STXD);
  output(GLO+RE);
  output(STR+R2);
  output(SEP+R2);
  output(DEC+R2);
  return line;
  }

