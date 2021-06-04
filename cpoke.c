#include "header.h"

char* cpoke(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          ghi   rc                      ; Get poke address");
  Asm("          stxd");
  Asm("          glo   rc");
  Asm("          stxd");
  line = cexpr(line);
  Asm("          irx                           ; Recover poke address");
  Asm("          ldxa");
  Asm("          plo   rf");
  Asm("          ldx");
  Asm("          phi   rf");
  Asm("          glo   rc                      ; Get low byte of poke value");
  Asm("          str   rf                      ; And write it to memory");
  return line;
  }

