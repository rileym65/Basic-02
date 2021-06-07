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
  Asm("          inc   r7                      ; Get poke address");
  Asm("          lda   r7");
  Asm("          stxd                          ; Store for now");
  Asm("          ldn   r7");
  Asm("          stxd");
  line = cexpr(line);
  Asm("          irx                           ; Recover poke address");
  Asm("          ldxa");
  Asm("          phi   rf");
  Asm("          ldx");
  Asm("          plo   rf");
  Asm("          inc   r7                      ; Get low byte of poke value");
  Asm("          lda   r7");
  Asm("          str   rf                      ; And write it to memory");
  return line;
  }

