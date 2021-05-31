#include "header.h"

char* cgoto(char* line) {
  word target;
  line = trim(line);
  line = getNumber(line, &target);
  if (target == 0) {
    showError("Invalid line number for goto");
    exit(1);
    }
  if (findLine(target, &target) != 0) {
    showError("Line number not found");
    exit(1);
    }
  output(LBR); output(target / 256); output(target % 256);
  return line;
  }

