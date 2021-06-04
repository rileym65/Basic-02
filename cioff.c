#include "header.h"

char* cioff(char* line) {
  word target;
  target = address;
  Asm("          sex   r3                      ; Set X=P");
  Asm("          dis                           ; Turn interrupts off");
  Asm("          db    023h");
  return line;
  }

