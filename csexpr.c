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

char* csexpr(char* line, int level) {
  int lab1;
  int lab2;
  char tmpvar1[16];
  char buffer[512];
  char buffer2[256];
  int  pos;
  sprintf(tmpvar1,"v_STMP%d_$", level);
  while (*line != 0 && *line != ':') {
    if (*line == '"') {
      lab1 = ++autoLabel;
      lab2 = ++autoLabel;
      sprintf(buffer,"          lbr   la_%d                    ; Jump past string data",lab2);
      Asm(buffer);
      pos = 0;
      line++;
      while (*line != '"' && *line != 0) {
        buffer2[pos++] = *line++;
        }
      buffer2[pos] = 0;
      if (*line != '"') {
        showError("Syntax error");
        while (*line != 0 && *line != ':') line++;
        return line;
        }
      line++;
      line = trim(line);
      sprintf(buffer,"la_%d:    db    '%s',0",lab1, buffer2);
      Asm(buffer);
      sprintf(buffer,"la_%d:",lab2, buffer2);
      Asm(buffer);
      sprintf(buffer,"          ldi   la_%d.1                  ; Get address of data",lab1);
      Asm(buffer);
      Asm(           "          phi   rf                       ; Place into RF");
      sprintf(buffer,"          ldi   la_%d.0                  ; Lsb of data",lab1);
      Asm(buffer);
      Asm(           "          plo   rf                       ; Place into RF");
      sprintf(buffer,"          ldi   %s.1                  ; Get address of data",tmpvar1);
      Asm(buffer);
      Asm(           "          phi   rd                       ; Place into RD");
      sprintf(buffer,"          ldi   %s.0                  ; Lsb of data",tmpvar1);
      Asm(buffer);
      Asm(           "          plo   rd                       ; Place into RD");
      Asm(           "          sep   scall                    ; Set the string");
      Asm(           "          dw    setstring");
      AddExternal(currentProc, "setstring");
      }

    }
  return line;
  }

