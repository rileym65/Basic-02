#include "header.h"

char* cdma(char* line) {
  word target;
  line = trim(line);
  line = cexpr(line);
  output(GLO+RC);
  output(PLO+R0);
  output(GHI+RC);
  output(PHI+R0);
  return line;
  }

