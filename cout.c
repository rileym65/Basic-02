#include "header.h"

char* cout(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          ldi   0d3h                    ; Need a SEP R3 command");
  Asm("          stxd                          ; Place on stack");
  Asm("          glo   rc                      ; Get port");
  Asm("          ani   7                       ; Keep only bottom 3 bits");
  Asm("          ori   060h                    ; Convert to OUT command");
  Asm("          stxd                          ; Place on stack");
  line = cexpr(line);
  Asm("          irx                           ; Recover OUT command");
  Asm("          ldx");
  Asm("          plo   re                      ; Set aside for a moment");
  Asm("          glo   rc                      ; Write OUT value to stack");
  Asm("          stxd");
  Asm("          glo   re                      ; Recover OUT command");
  Asm("          str   r2                      ; Place back on stack");
  Asm("          sep   r2                      ; Execute code on stack");
  Asm("          dec   r2                      ; Put stack pointer back where it belongs");
  return line;
  }

