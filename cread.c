#include "header.h"

char* cread(char* line) {
  word last;
  int  pos;
  word addr;
  word num;
  char neg;
  char token[128];
  last = 0xffff;
  line = trim(line);
  addr = getVariable("DATA_");
  Asm("          ldi   [DATA_].1               ; Point to DATA pointer");
  Asm("          phi   rf");
  Asm("          ldi   [DATA_].0");
  Asm("          plo   rf");
  Asm("          lda   rf                      ; Retrieve DATA pointer");
  Asm("          phi   rd");
  Asm("          ldn   rf                      ; Retrieve DATA pointer");
  Asm("          plo   rd");
  while (*line != ':' && *line != 0) {
    if ((*line < 'a' || *line > 'z') &&
        (*line < 'A' || *line > 'Z')) {
      showError("Syntax error");
      exit(1);
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
            *line == '_') {
      token[pos++] = *line;
      token[pos] = 0;
      line++;
      }
    addr = getVariable(token);
    if (last == 0xffff || ((addr & 0xff00) != (addr & 0xff00))) {
      sprintf(buffer,"          ldi   [%s].1               ; Point to variable",token); Asm(buffer);
      Asm("          phi   rc");
      }
    sprintf(buffer,"          ldi   [%s].0               ; Point to variable",token); Asm(buffer);
    Asm("          plo   rc");
    Asm("          lda   rd                      ; Retrieve data from DATA pool");
    Asm("          str   rc                      ; And store into variable");
    Asm("          inc   rc");
    Asm("          lda   rd");
    Asm("          str   rc");
    if (use32Bits) {
      Asm("          inc   rc");
      Asm("          lda   rd");
      Asm("          str   rc");
      Asm("          inc   rc");
      Asm("          lda   rd");
      Asm("          str   rc");
      }
    last = addr;
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') {
      line++;
      line = trim(line);
      }
    }
  Asm("          glo   rd                      ; Save DATA pointer");
  Asm("          str   rf");
  Asm("          dec   rf");
  Asm("          ghi   rd");
  Asm("          str   rf");
  return line;
  }

