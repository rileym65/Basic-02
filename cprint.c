#include "header.h"

char* cprint(char* line) {
  char qt;
  char last;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  last = ' ';
  while (*line != ':' && *line != 0) {
    line=trim(line);
    if (*line == '"') {
      Asm("          sep   scall                   ; Display message");
      Asm("          dw    f_inmsg");
      strcpy(buffer,"          db    '");
      line++;
      while (*line != '"' && *line != 0) {
        buffer[strlen(buffer)+1] = 0;
        buffer[strlen(buffer)] = *line++;
        }
      strcat(buffer,"',0"); Asm(buffer);
      if (*line == '"') line++;
      last = ' ';
      }
    else if (*line == ',') {
      Asm("          ldi   9                       ; Display a tab character");
      Asm("          sep   scall                   ; Display cr/lf");
      Asm("          dw    f_type");
      line++;
      last = ',';
      }
    else if (*line == ';') {
      line++;
      last = ';';
      }
    else {
      line = cexpr(line);
      Asm("          sep   scall                   ; Display integer value");
      Asm("          dw    itoa");
      last = ' ';
      }
    }
  if (last != ';' && last != ',') {
    Asm("          sep   scall                   ; Display cr/lf");
    Asm("          dw    f_inmsg");
    Asm("          db    10,13,0");
    }
  return line;
  }

