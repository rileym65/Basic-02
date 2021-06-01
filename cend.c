#include "header.h"

char* cend(char* line) {
  word target;
  target = address;
  if (exitAddress != 0xffff) {
    output(LBR); output(exitAddress / 256); output(exitAddress % 256);
    }
  else if (useElfos) {
    target = 0x303;
    output(LBR); output(target / 256); output(target % 256);
    }
  else {
    output(IDL);
    output(LBR); output(target / 256); output(target % 256);
    }
  return line;
  }

