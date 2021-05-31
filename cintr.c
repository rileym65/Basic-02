#include "header.h"

char* cintr(char* line) {
  word target;
  line = trim(line);
  line = getNumber(line, &target);
  if (target == 0) {
    showError("Invalid line number for intr");
    exit(1);
    }
  if (findLine(target, &target) != 0) {
    showError("Line number not found");
    exit(1);
    }
  output(LDI); output(target / 256);
  output(PHI+R1);
  output(LDI); output(target % 256);
  output(PLO+R1);
  return line;
  }

