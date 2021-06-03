#include "header.h"

char* cdata(char* line) {
  int  pos;
  word addr;
  word num;
  char neg;
  line = trim(line);
  while (*line != ':' && *line != 0) {
    if ((*line < '0' || *line > '9') && *line != '-') {
      showError("Syntax error");
      exit(1);
      }
    neg = 0;
    num = 0;
    if (*line == '-') {
      neg = -1;
      line++;
      }
    while (*line >= '0' && *line <= '9') {
      num = (num * 10) + (*line - '0');
      line++;
      }
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (neg) {
      num = (num ^ 0xffff) + 1;
      }
    if (passNumber == 1) {
      numData++;
      if (numData == 1)
        data = (word*)malloc(sizeof(word));
      else
        data = (word*)realloc(data, sizeof(word) * numData);
      data[numData-1] = num;
      }
    if (*line == ',') {
      line++;
      line = trim(line);
      }
    }
  return line;
  }

