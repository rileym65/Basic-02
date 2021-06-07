#include "header.h"

char* cinput(char* line) {
  char qt;
  word addr;
  char name[256];
  int  pos;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  if (*line = '"') {
    Asm("          sep   scall                   ; Display prompt");
    Asm("          dw    f_inmsg");
    strcpy(buffer,"          db    '");
    line++;
    while (*line != '"' && *line != 0) {
      buffer[strlen(buffer)+1] = 0;
      buffer[strlen(buffer)] = *line++;
      }
    strcat(buffer,"',0"); Asm(buffer);
    if (*line == '"') line++;
    line = trim(line);
    if (*line != ',') {
      showError("Syntax error");
      exit(1);
      }
    }
  line++;
  while (*line != ':' && *line != 0) {
    if (!(*line >= 'a' && *line <= 'z') &&
        !(*line >= 'A' && *line <= 'Z')) {
      showError("Syntax error");
      exit(1);
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') {
      name[pos++] = *line++;
      }
    name[pos] = 0;
    if (strlen(name) == 0) {
      showError("Syntax error");
      exit(1);
      }
    addr = getVariable(name);
    Asm("          ldi   [iobuffer].1            ; Point to keyboard buffer");
    Asm("          phi   rf");
    Asm("          ldi   [iobuffer].0");
    Asm("          plo   rf");
    Asm("          sep   scall                   ; Get input from user");
    Asm("          dw    f_input");
    Asm("          ldi   [iobuffer].1            ; Point to keyboard buffer");
    Asm("          phi   rf");
    Asm("          ldi   [iobuffer].0");
    Asm("          plo   rf");
    Asm("          sep   scall                   ; Convert ASCII to integer");
    Asm("          dw    atoi");
    sprintf(buffer,"          ldi   [%s].1              ; Point to destination variable",name); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s].0",name); Asm(buffer);
    Asm("          plo   rf");
    Asm("          ghi   rc                      ; Store value into variable");
    Asm("          str   rf");
    Asm("          inc   rf");
    Asm("          glo   rc");
    Asm("          str   rf");
    Asm("          sep   scall                   ; Display cr/lf");
    Asm("          dw    f_inmsg");
    Asm("          db    10,13,0");
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') line++;
    }
  return line;
  }

