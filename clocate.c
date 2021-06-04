#include "header.h"

char* clocate(char* line) {
  int  pos;
  word addr;
  Asm("          sep   scall                   ; Send first portion of escape sequence");
  Asm("          dw    f_inmsg");
  Asm("          db    27,'[',0");
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          sep   scall                   ; Send row");
  Asm("          dw    itoa");
  Asm("          ldi   ';'                     ; Next need a semicolon");
  Asm("          sep   scall                   ; Send it");
  Asm("          dw    f_type");
  line = cexpr(line);
  Asm("          sep   scall                   ; Send column");
  Asm("          dw    itoa");
  Asm("          ldi   'H'                     ; Lastly need an H");
  Asm("          sep   scall                   ; Send it");
  Asm("          dw    f_type");
  return line;
  }

