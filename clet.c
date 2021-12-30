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

char* clet(char* line) {
  int  pos;
  int  fp;
  int  st;
  word addr;
  dword value;
  char varname[256];
  line = trim(line);
  /* ********************************** */
  /* ***** Look for optimizations ***** */
  /* ********************************** */
  if (match(line,"A=#")) {
    addr = getVariable(matches[0]);
    value = atoi(matches[2]);
    sprintf(buffer,"          ldi   v_%s.1                  ; Get variable address", matches[0]); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   v_%s.0", matches[0]); Asm(buffer);
    Asm("          plo   rf");
    if (use32Bits) {
      sprintf(buffer,"          ldi   %d                      ; Write value to variable", (value & 0xff000000) >> 24); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      sprintf(buffer,"          ldi   %d", (value & 0xff0000) >> 16); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      }

    sprintf(buffer,"          ldi   %d                      ; Write value to variable", (value & 0xff00) >> 8); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   %d", value & 0xff); Asm(buffer);
    Asm("          str   rf");
    while (*line != 0 && *line != ':') line++;
    return line;
    }
  if (match(line,"A=A")) {
    addr = getVariable(matches[0]);
    sprintf(buffer,"          ldi   v_%s.1                  ; Get first variable address", matches[0]); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   v_%s.0", matches[0]); Asm(buffer);
    Asm("          plo   rf");
    addr = getVariable(matches[2]);
    sprintf(buffer,"          ldi   v_%s.1                  ; Get second variable address", matches[2]); Asm(buffer);
    Asm("          phi   rd");
    sprintf(buffer,"          ldi   v_%s.0", matches[2]); Asm(buffer);
    Asm("          plo   rd");
    Asm("          lda   rd                      ; Transfer value");
    Asm("          str   rf");
    Asm("          inc   rf");
    if (use32Bits) {
      Asm("          lda   rd");
      Asm("          str   rf");
      Asm("          inc   rf");
      Asm("          lda   rd");
      Asm("          str   rf");
      Asm("          inc   rf");
      }
    Asm("          ldn   rd");
    Asm("          str   rf");
    while (*line != 0 && *line != ':') line++;
    return line;
    }
  if (match(line,"A=A+#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      if (use32Bits) {
        sprintf(buffer,"          ldi   (v_%s+3).1              ; Get variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      else {
        sprintf(buffer,"          ldi   (v_%s+1).1              ; Get variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      Asm("          ldn   rf");
      sprintf(buffer,"          adi   %d                      ; Add in constant value", value & 0xff); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          adci  %d", (value & 0xff00) >> 8); Asm(buffer);
      Asm("          str   rf");
      if (use32Bits) {
        Asm("          dec   rf");
        Asm("          ldn   rf");
        sprintf(buffer,"          adci  %d", (value & 0xff0000) >> 16); Asm(buffer);
        Asm("          str   rf");
        Asm("          dec   rf");
        Asm("          ldn   rf");
        sprintf(buffer,"          adci  %d", (value & 0xff000000) >> 24); Asm(buffer);
        Asm("          str   rf");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      if (use32Bits) {
        sprintf(buffer,"          ldi   (v_%s+3).1                ; Get first variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   (v_%s+3).1                ; Get second variable address +3", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      else {
        sprintf(buffer,"          ldi   (v_%s+1).1                ; Get first variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   (v_%s+1).1                ; Get second variable address +1", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      Asm("          ldn   rd");
      sprintf(buffer,"          adi   %d                      ; Add in constant value", value & 0xff); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          dec   rd");
      Asm("          ldn   rd");
      sprintf(buffer,"          adci  %d", (value & 0xff00) >> 8); Asm(buffer);
      Asm("          str   rf");
      if (use32Bits) {
        Asm("          dec   rf");
        Asm("          dec   rd");
        Asm("          ldn   rd");
        sprintf(buffer,"          adci  %d", (value & 0xff0000) >> 16); Asm(buffer);
        Asm("          str   rf");
        Asm("          dec   rf");
        Asm("          dec   rd");
        Asm("          ldn   rd");
        sprintf(buffer,"          adci  %d", (value & 0xff000000) >> 24); Asm(buffer);
        Asm("          str   rf");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    }
  if (match(line,"A=A-#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      if (use32Bits) {
        sprintf(buffer,"          ldi   (v_%s+3).1              ; Get variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      else {
        sprintf(buffer,"          ldi   (v_%s+1).1              ; Get variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      Asm("          ldn   rf");
      sprintf(buffer,"          smi   %d                      ; Add in constant value", value & 0xff); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          smbi  %d", (value & 0xff00) >> 8); Asm(buffer);
      Asm("          str   rf");
      if (use32Bits) {
        Asm("          dec   rf");
        Asm("          ldn   rf");
        sprintf(buffer,"          smbi  %d", (value & 0xff0000) >> 16); Asm(buffer);
        Asm("          str   rf");
        Asm("          dec   rf");
        Asm("          ldn   rf");
        sprintf(buffer,"          smbi  %d", (value & 0xff000000) >> 24); Asm(buffer);
        Asm("          str   rf");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      if (use32Bits) {
        sprintf(buffer,"          ldi   (v_%s+3).1                ; Get first variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   (v_%s+3).1                ; Get second variable address +3", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   (v_%s+3).0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      else {
        sprintf(buffer,"          ldi   (v_%s+1).1                ; Get first variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   (v_%s+1).1                ; Get second variable address +1", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   (v_%s+1).0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      Asm("          ldn   rd");
      sprintf(buffer,"          smi   %d                      ; Add in constant value", value & 0xff); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          dec   rd");
      Asm("          ldn   rd");
      sprintf(buffer,"          smbi  %d", (value & 0xff00) >> 8); Asm(buffer);
      Asm("          str   rf");
      if (use32Bits) {
        Asm("          dec   rf");
        Asm("          dec   rd");
        Asm("          ldn   rd");
        sprintf(buffer,"          smbi  %d", (value & 0xff0000) >> 16); Asm(buffer);
        Asm("          str   rf");
        Asm("          dec   rf");
        Asm("          dec   rd");
        Asm("          ldn   rd");
        sprintf(buffer,"          smbi  %d", (value & 0xff000000) >> 24); Asm(buffer);
        Asm("          str   rf");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    }
  /* ********************************** */
  if (!(*line >= 'a' && *line <= 'z') && !(*line >= 'A' && *line <= 'Z')) {
    showError("Invalid variable name");
    *line = 0;
    return line;
    }
  pos = 0;
  fp = 0;
  st = 0;
  while ((*line >= 'a' && *line <= 'z') ||
         (*line >= 'A' && *line <= 'Z') ||
         (*line >= '0' && *line <= '9') ||
         *line == '_') {
    varname[pos++] = *line++;
    if (*line == '$') {
      varname[pos++] = *line++;
      st = -1;
      if ((*line >= 'a' && *line <= 'z') ||
          (*line >= 'A' && *line <= 'Z') ||
          (*line >= '0' && *line <= '9') ||
          *line == '_') {
          showError("Invalid variable name");
          *line = 0;
          return line;
        }
      }
    if (useFp) {
      if (*line == '!') {
        varname[pos++] = *line++;
        fp = -1;
        if ((*line >= 'a' && *line <= 'z') ||
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
  varname[pos] = 0;
  line = trim(line);
  if (*line != '=') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line++;
  line = trim(line);
  if (st) {
    }
  else {
    if (fp) line = cexpr(line, 1);
      else line = cexpr(line, 0);
    if (exprErrors > 0) return line;
    line = trim(line);
    if (*line != ':' && *line > ' ') {
      showError("Syntax error");
      *line = 0;
      return line;
      }
    addr = getVariable(varname);
    if (use32Bits) {
      sprintf(buffer,"          ldi   (v_%s+3).1              ; Get destination variable address", varname); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   (v_%s+3).0", varname); Asm(buffer);
      Asm("          plo   rf");
      }
    else  {
      sprintf(buffer,"          ldi   (v_%s+1).1              ; Get destination variable address", varname); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   (v_%s+1).0", varname); Asm(buffer);
      Asm("          plo   rf");
      }
    Asm("          inc   r7                        ; Write expresison result to variable");
    Asm("          lda   r7");
    Asm("          str   rf");
    Asm("          dec   rf");
    if (use32Bits) {
      Asm("          lda   r7");
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          lda   r7");
      Asm("          str   rf");
      Asm("          dec   rf");
      }
    Asm("          ldn   r7");
    Asm("          str   rf");
    }
  while (*line != 0) line++;
  return line;
  }

