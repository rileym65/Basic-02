#include "header.h"

char* trim(char* line) {
  while (*line == ' ' || *line == '\t') line++;
  return line;
  }

