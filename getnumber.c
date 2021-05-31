#include "header.h"

char* getNumber(char* line, word* number) {
  *number = 0;
  while (*line >= '0' && *line <= '9') {
    *number = (*number * 10) + (*line - '0');
    line++;
    }
  return line;
  }

