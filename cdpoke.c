#include "header.h"

char* cdpoke(char* line) {
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
  Asm("          ghi   rc                      ; Get high byte of poke value");
  Asm("          str   rf                      ; And write it to memory");
  Asm("          inc   rf");
  Asm("          glo   rc                      ; Get low byte of poke value");
  Asm("          str   rf                      ; And write it to memory");
  return line;
  }

