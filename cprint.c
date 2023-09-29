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

char* cprint(char* line) {
  int  pos;
  char qt;
  char last;
  char varname[256];
  char buffer[512];
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
  last = ' ';
  while (*line != ':' && *line != 0) {
    line=trim(line);
    if (*line == '"') {
      Asm("          sep   scall                   ; Display message");
      Asm("          dw    f_inmsg");
      strcpy(buffer,"          db    '");
      line++;
      while (*line != '"' && *line != 0) {
        if (*line == '\'') {
          strcat(buffer,"',39,'");
          line++;
          }
        else {
          buffer[strlen(buffer)+1] = 0;
          buffer[strlen(buffer)] = *line++;
          }
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
      pos = 0;
      while ((line[pos] >= 'a' && line[pos] <= 'z') ||
             (line[pos] >= 'A' && line[pos] <= 'Z') ||
             (line[pos] >= '0' && line[pos] <= '9') ||
             line[pos] == '_') varname[pos++] = line[pos];
      varname[pos] = 0;
      if (line[pos] == '$') {
        sprintf(buffer,"          ldi   v_%s$.1              ; Display result",varname);
        Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   v_%s$.0",varname);
        Asm(buffer);
        Asm("          plo   rd");
        Asm("          ldi   iobuffer.1              ; Display result");
        Asm("          phi   rf");
        Asm("          ldi   iobuffer.0");
        Asm("          plo   rf");
        Asm("          sep   scall");
        Asm("          dw    printstring");
        AddExternal(currentProc, "printstring");
        Asm("          ldi   iobuffer.1              ; Display result");
        Asm("          phi   rf");
        Asm("          ldi   iobuffer.0");
        Asm("          plo   rf");
        Asm("          sep   scall");
        Asm("          dw    f_msg");
        AddExternal(currentProc, "printstring");
        while (*line != 0 && *line != '$') line++;
        if (*line == '$') line++;
        last = ' ';
        }
      else {
        line = cexpr(line, 2);
        if (exprErrors > 0) return line;
        if (useFp) {
          if (tokens[1] == OP_NUM) {
            Asm("          inc   r7                      ; Point to expression result");
            Asm("          glo   r7");
            Asm("          plo   rf");
            Asm("          ghi   r7");
            Asm("          phi   rf");
            Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
            Asm("          phi   rd");
            Asm("          ldi   iobuffer.0");
            Asm("          plo   rd");
            Asm("          sep   scall                   ; Display integer value");
            Asm("          dw    itoa32");
            Asm("          ldi   iobuffer.1              ; Display result");
            Asm("          phi   rf");
            Asm("          ldi   iobuffer.0");
            Asm("          plo   rf");
            Asm("          sep   scall");
            Asm("          dw    f_msg");
            Asm("          inc   r7                      ; Remove expression result");
            Asm("          inc   r7");
            Asm("          inc   r7");
            AddExternal(currentProc, "itoa32");
            }
          else if (tokens[1] == OP_NUMFP) {
            Asm("          inc   r7                      ; Point to expression result");
            Asm("          glo   r7");
            Asm("          plo   rf");
            Asm("          ghi   r7");
            Asm("          phi   rf");
            Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
            Asm("          phi   rd");
            Asm("          ldi   iobuffer.0");
            Asm("          plo   rd");
            Asm("          sep   scall                   ; Display floating point value");
            Asm("          dw    ftoa");
            Asm("          ldi   iobuffer.1              ; Display result");
            Asm("          phi   rf");
            Asm("          ldi   iobuffer.0");
            Asm("          plo   rf");
            Asm("          sep   scall");
            Asm("          dw    f_msg");
            Asm("          inc   r7                      ; Remove expression result");
            Asm("          inc   r7");
            Asm("          inc   r7");
            AddExternal(currentProc, "ftoa");
            }
          else {
            showError("Expression error\n");
            *line = 0;
            return line;
            }
          }
        else if (use32Bits) {
          Asm("          inc   r7                      ; Point to expression result");
          Asm("          glo   r7");
          Asm("          plo   rf");
          Asm("          ghi   r7");
          Asm("          phi   rf");
          Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
          Asm("          phi   rd");
          Asm("          ldi   iobuffer.0");
          Asm("          plo   rd");
          Asm("          sep   scall                   ; Display integer value");
          Asm("          dw    itoa32");
          Asm("          ldi   iobuffer.1              ; Display result");
          Asm("          phi   rf");
          Asm("          ldi   iobuffer.0");
          Asm("          plo   rf");
          Asm("          sep   scall");
          Asm("          dw    f_msg");
          Asm("          inc   r7                      ; Remove expression result");
          Asm("          inc   r7");
          Asm("          inc   r7");
          AddExternal(currentProc, "itoa32");
          }
        else {
          Asm("          inc   r7                      ; Recover expression result");
          Asm("          lda   r7");
          Asm("          plo   rc");
          Asm("          ldn   r7");
          Asm("          phi   rc");
          Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
          Asm("          phi   rd");
          Asm("          ldi   iobuffer.0");
          Asm("          plo   rd");
          Asm("          sep   scall                   ; Display integer value");
          Asm("          dw    itoa");
          Asm("          ldi   iobuffer.1              ; Display result");
          Asm("          phi   rf");
          Asm("          ldi   iobuffer.0");
          Asm("          plo   rf");
          Asm("          sep   scall");
          Asm("          dw    f_msg");
          AddExternal(currentProc, "itoa");
          }
        last = ' ';
        }
      }
    line=trim(line);
    }
  if (last != ';' && last != ',') {
    Asm("          sep   scall                   ; Display cr/lf");
    Asm("          dw    f_inmsg");
    Asm("          db    10,13,0");
    }
  return line;
  }

