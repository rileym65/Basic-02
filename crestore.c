/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "header.h"

char* crestore(char* line) {
  int  i;
  word pos;
  word num;
  line = trim(line);
  pos = 0;
  if (passNumber == 2) {
    if (*line != ':' && *line != 0) {
      if (*line < '0' || *line > '9') {
        showError("Invalid line number");
        *line = 0;
        return line;
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
        *line = 0;
        return line;
        }
      }
    }
  else {
    while (*line != ':' && *line != 0) line++;
    }
  line = trim(line);
  Asm("          ldi   DATA_.1                 ; Get address of DATA pointer");
  Asm("          phi   rf");
  Asm("          ldi   DATA_.0");
  Asm("          plo   rf");

  if (use32Bits) {
    sprintf(buffer,"          ldi   (%d*4+data).1           ; Need a SEP R3 command",pos); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   (%d*4+data).0",pos); Asm(buffer);
    Asm("          str   rf");
    }
  else {
    sprintf(buffer,"          ldi   (%d*2+data).1           ; Need a SEP R3 command",pos); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   (%d*2+data).0",pos); Asm(buffer);
    Asm("          str   rf");
    }
  return line;
  }

