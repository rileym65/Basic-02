#include "header.h"

char* creturn(char* line) {
  word target;
  Asm("          sep   sret                    ; Return");
  return line;
  }

