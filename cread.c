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
  int  pos;
  int  lab;
  word addr;
  int  string;
  char token[128];
  useData = -1;
  string = 0;
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
            *line == '_' || *line == '!' || *line == '$') {
      token[pos++] = *line;
      token[pos] = 0;
      line++;
      }
    addr = getVariable(token);
    if (token[strlen(token)-1] == '$') {
      Asm("          ldi   iobuffer.1              ; point to temporary memory");
      Asm("          phi   rc");
      Asm("          ldi   iobuffer.0");
      Asm("          plo   rc");
      lab = ++autoLabel;
      sprintf(buffer,"lbl_%d:",lab); Asm(buffer);
      Asm("          lda   rd                      ; get byte from data pool");
      Asm("          str   rc                      ; write to temp space");
      Asm("          inc   rc                      ; Point to next position");
      sprintf(buffer,"          lbnz  lbl_%d               ; Loop until terminator",lab); Asm(buffer);
      Asm("          glo   rd                      ; Save data position");
      Asm("          stxd");
      Asm("          ghi   rd");
      Asm("          stxd");
      Asm("          ldi   iobuffer.1              ; point to temporary memory");
      Asm("          phi   rf");
      Asm("          ldi   iobuffer.0");
      Asm("          plo   rf");
      sprintf(buffer,"          ldi   v_%s.1               ; Point to variable",token); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   v_%s.0               ; Point to variable",token); Asm(buffer);
      Asm("          plo   rd");
      Asm("          sep   scall                   ; Set the string");
      Asm("          dw    setstring");
      AddExternal(currentProc, "setstring");
      Asm("          irx                           ; Recover data position");
      Asm("          ldxa");
      Asm("          phi   rd");
      Asm("          ldx");
      Asm("          plo   rd");
      string = -1;
      }
    else {
      sprintf(buffer,"          ldi   v_%s.1               ; Point to variable",token); Asm(buffer);
      Asm("          phi   rc");
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
      }
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
  if (string) {
    Asm("          ldi   DATA_.1                 ; Point to DATA pointer");
    Asm("          phi   rf");
    Asm("          ldi   DATA_.0");
    Asm("          plo   rf");
    }
  Asm("          ghi   rd                      ; Save DATA pointer");
  Asm("          str   rf");
  Asm("          inc   rf");
  Asm("          glo   rd");
  Asm("          str   rf");
  return line;
  }

