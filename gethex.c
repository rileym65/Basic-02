#include "header.h"

word getHex(char* line) {
  word number;
  number = 0;
  while ((*line >= '0' && *line <= '9') ||
         (*line >= 'a' && *line <= 'f') ||
         (*line >= 'A' && *line <= 'F')) {
    if (*line >= '0' && *line <= '9') number = (number << 4) + (*line - '0');
    if (*line >= 'a' && *line <= 'f') number = (number << 4) + (*line - 'a') + 10;
    if (*line >= 'A' && *line <= 'F') number = (number << 4) + (*line - 'A') + 10;
    line++;
    }
  return number;
  }

