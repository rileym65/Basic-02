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

char* cread(char* line) {
  word last;
  int  pos;
  word addr;
  char token[128];
  last = 0xffff;
  line = trim(line);
  Asm("          ldi   DATA_.1                 ; Point to DATA pointer");
  Asm("          phi   rf");
  Asm("          ldi   DATA_.0");
  Asm("          plo   rf");
  Asm("          lda   rf                      ; Retrieve DATA pointer");
  Asm("          phi   rd");
  Asm("          ldn   rf                      ; Retrieve DATA pointer");
  Asm("          plo   rd");
  while (*line != ':' && *line != 0) {
    if ((*line < 'a' || *line > 'z') &&
        (*line < 'A' || *line > 'Z')) {
      showError("Syntax error");
      *line = 0;
      return line;
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
    if (last == 0xffff || ((addr & 0xff00) != (last & 0xff00))) {
      sprintf(buffer,"          ldi   v_%s.1               ; Point to variable",token); Asm(buffer);
      Asm("          phi   rc");
      }
    sprintf(buffer,"          ldi   v_%s.0               ; Point to variable",token); Asm(buffer);
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
      *line = 0;
      return line;
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

