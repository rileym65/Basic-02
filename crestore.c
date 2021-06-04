#include "header.h"

char* crestore(char* line) {
  int  i;
  word pos;
  word num;
  word addr;
  char hasVar;
  char varname[256];
  line = trim(line);
  hasVar = 0;
  pos = 0;
  if (passNumber == 2) {
    if (*line != ':' && *line != 0) {
      if (*line < '0' || *line > '9') {
        showError("Invalid line number");
        exit(1);
        }
      num = 0;
      while (*line >= '0' && *line <= '9') {
        num = (num * 10) + (*line - '0');
        line++;
        }
      pos = 0xffff;
      for (i=0; i<numDataLines; i++) {
        if (dataLines[i] == num) {
          pos = dataPositions[i];
          i = numDataLines;
          }
        }
      if (pos == 0xffff) {
        showError("Line number not found");
        exit(1);
        }
      }
    }
  else {
    while (*line != ':' && *line != 0) line++;
    }
  line = trim(line);
  addr = getVariable("DATA_");
  Asm("          ldi   [DATA_].1               ; Get address of DATA pointer");
  Asm("          phi   rf");
  Asm("          ldi   [DATA_].0");
  Asm("          plo   rf");

  addr = dataAddress + (pos * 2);
  output(LDI); output(addr/256); output(STR+RF); output(INC+RF);
  output(LDI); output(addr%256); output(STR+RF);
  if (useAsm) {
    sprintf(buffer,"          ldi   DATA_.1"); writeAsm(buffer,"Get address of DATA pointer");
    sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ldi   DATA_.0"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ldi   (data+(%d*2)).1",pos); writeAsm(buffer,"And set to new position");
    sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          inc   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ldi   (data+(%d*2)).0",pos); writeAsm(buffer,"");
    sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
    }
  return line;
  }

