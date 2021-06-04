#include "header.h"

char* cidle(char* line) {
  Asm("          idl                           ; Idle the CPU");
  line = trim(line);
  return line;
  }

