#include "header.h"

char* cend(char* line) {
  word target;
  target = address;
  if (useElfos) {
    target = 0x303;
    output(LBR); output(target / 256); output(target % 256);
    }
  else {
    output(IDL);
    output(LBR); output(target / 256); output(target % 256);
    }
  return line;
  }

