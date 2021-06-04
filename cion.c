#include "header.h"

char* cion(char* line) {
  word target;
  target = address;
  Asm("          sex   r3                      ; Set X=P");
  Asm("          ret                           ; Turn interrupts on");
  Asm("          db    023h");
  return line;
  }

