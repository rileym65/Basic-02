#include "header.h"

char* cq(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line);
  output(GLO+RC);
  addr = address + 7;
  output(LBZ); output(addr/256); output(addr%256);
  output(REQ);
  addr = address + 4;
  output(LBR); output(addr/256); output(addr%256);
  output(SEQ);
  return line;
  }

