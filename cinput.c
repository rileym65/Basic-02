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

char* cinput(char* line) {
  int  fp;
  char qt;
  char name[256];
  int  pos;
  useTerminal = -1;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  if (*line == '"') {
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
      *line = 0;
      return line;
      }
    line++;
    }
  fp = 0;
  line = trim(line);
  while (*line != ':' && *line != 0) {
    if (!(*line >= 'a' && *line <= 'z') &&
        !(*line >= 'A' && *line <= 'Z')) {
      showError("Syntax error");
      *line = 0;
      return line;
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') {
      name[pos++] = *line++;
      if (useFp) {
        if (*line == '!') {
          name[pos++] = *line++;
          fp = -1;
          while ((*line >= 'a' && *line <= 'z') ||
                 (*line >= 'A' && *line <= 'Z') ||
                 (*line >= '0' && *line <= '9') ||
                 *line == '_') {
            showError("Invalid variable name");
            *line = 0;
            return line;
            }
          }
        }
      }
    if (*line == '$') name[pos++] = *line++;
    name[pos] = 0;
    if (strlen(name) == 0) {
      showError("Syntax error");
      *line = 0;
      return line;
      }
    getVariable(name);
    Asm("          sep   scall                   ; display question mark");
    Asm("          dw    f_inmsg");
    Asm("          db    '? ',0");
    Asm("          ldi   iobuffer.1              ; Point to keyboard buffer");
    Asm("          phi   rf");
    Asm("          ldi   iobuffer.0");
    Asm("          plo   rf");
    Asm("          sep   scall                   ; Get input from user");
    Asm("          dw    f_input");
    Asm("          ldi   iobuffer.1              ; Point to keyboard buffer");
    Asm("          phi   rf");
    Asm("          ldi   iobuffer.0");
    Asm("          plo   rf");
    if (name[pos-1] == '$') {
      sprintf(buffer,"          ldi   v_%s.1              ; Point to destination variable",name); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   v_%s.0",name); Asm(buffer);
      Asm("          plo   rd");
      Asm("          sep   scall                   ; Send data to string variable");
      Asm("          dw    setstring");
      AddExternal(currentProc, "setstring");
      }
    else if (fp && name[pos-1] == '!') {
      sprintf(buffer,"          ldi   v_%s.1              ; Point to destination variable",name); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   v_%s.0",name); Asm(buffer);
      Asm("          plo   rd");
      Asm("          sep   scall                   ; Convert ASCII to integer");
      Asm("          dw    atof");
      AddExternal(currentProc, "atof");
      }
    else if (use32Bits) {
      sprintf(buffer,"          ldi   v_%s.1              ; Point to destination variable",name); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   v_%s.0",name); Asm(buffer);
      Asm("          plo   rd");
      Asm("          sep   scall                   ; Convert ASCII to integer");
      Asm("          dw    atoi32");
      AddExternal(currentProc, "atoi32");
      }
    else {
      Asm("          sep   scall                   ; Convert ASCII to integer");
      Asm("          dw    atoi");
      sprintf(buffer,"          ldi   v_%s.1              ; Point to destination variable",name); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   v_%s.0",name); Asm(buffer);
      Asm("          plo   rf");
      Asm("          ghi   rc                      ; Store value into variable");
      Asm("          str   rf");
      Asm("          inc   rf");
      Asm("          glo   rc");
      Asm("          str   rf");
      AddExternal(currentProc, "atoi");
      }
    Asm("          sep   scall                   ; Display cr/lf");
    Asm("          dw    f_inmsg");
    Asm("          db    10,13,0");
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      *line = 0;
      return line;
      }
    if (*line == ',') line++;
    }
  return line;
  }

