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
  if (use32Bits) {
    sprintf(buffer,"          ldi   %d*4+data.1             ; Need a SEP R3 command",pos); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   %d*4+data.0",pos); Asm(buffer);
    Asm("          str   rf");
    }
  else {
    sprintf(buffer,"          ldi   %d*2+data.1             ; Need a SEP R3 command",pos); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   %d*2+data.0",pos); Asm(buffer);
    Asm("          str   rf");
    }
  return line;
  }

