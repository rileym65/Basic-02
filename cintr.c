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
  Asm("          ldi   [INTR_].1               ; Point to interrupt line");
  Asm("          phi   rf");
  Asm("          ldi   [INTR_].0");
  Asm("          plo   rf");
  sprintf(buffer,"          ldi   0%xh                     ; Set to specified line",target/256); Asm(buffer);
  Asm("          str   rf");
  Asm("          inc   rf");
  sprintf(buffer,"          ldi   0%xh",target%256); Asm(buffer);
  Asm("          str   rf");
  return line;
  }

