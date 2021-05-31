#include "header.h"

char* cioff(char* line) {
  word target;
  target = address;
  output(SEX+R3);
  output(DIS); output(0x23);
  return line;
  }

