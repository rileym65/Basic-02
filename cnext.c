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

char* cnext(char* line) {
  int  pos;
  word addr;
  char hasVar;
  char varname[256];
  line = trim(line);
  hasVar = 0;
  if (*line == ':' || *line == 0) {
    addr = 0;
    }
  else {
    if (!(*line >= 'a' && *line <= 'z') && !(*line >= 'A' && *line <= 'Z')) {
      showError("Invalid variable name");
      exit(1);
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') {
      varname[pos++] = *line++;
      }
    varname[pos] = 0;
    line = trim(line);
    addr = getVariable(varname);
    hasVar = -1;
    }
  if (hasVar == 0) {
    Asm("          sep   scall                   ; Call NEXT handler");
    if (use32Bits) Asm("          dw    next32");
      else Asm("          dw    next");
    }
  else {
    sprintf(buffer,"          ldi   v_%s.1                   ; Get loop variable address",varname); Asm(buffer);
    Asm("          phi   rc");
    sprintf(buffer,"          ldi   v_%s.0",varname); Asm(buffer);
    Asm("          plo   rc");
    Asm("          sep   scall                   ; Call NEXT with var handler");
    if (use32Bits) Asm("          dw    nextvar32");
      else Asm("          dw    nextvar");
    }

  return line;
  }

