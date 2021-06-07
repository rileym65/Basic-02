#include "header.h"

char* clet(char* line) {
  int  pos;
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
    sprintf(buffer,"          ldi   [%s].1                  ; Get variable address", matches[0]); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s].0", matches[0]); Asm(buffer);
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
    sprintf(buffer,"          ldi   [%s].1                  ; Get first variable address", matches[0]); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s].0", matches[0]); Asm(buffer);
    Asm("          plo   rf");
    addr = getVariable(matches[2]);
    sprintf(buffer,"          ldi   [%s].1                  ; Get second variable address", matches[2]); Asm(buffer);
    Asm("          phi   rd");
    sprintf(buffer,"          ldi   [%s].0", matches[2]); Asm(buffer);
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
        sprintf(buffer,"          ldi   [%s]+3.1                ; Get variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      else {
        sprintf(buffer,"          ldi   [%s]+1.1                ; Get variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
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
        sprintf(buffer,"          ldi   [%s]+3.1                  ; Get first variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   [%s]+3.1                  ; Get second variable address +3", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      else {
        sprintf(buffer,"          ldi   [%s]+1.1                  ; Get first variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   [%s]+1.1                  ; Get second variable address +1", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[2]); Asm(buffer);
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
        sprintf(buffer,"          ldi   [%s]+3.1                ; Get variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        }
      else {
        sprintf(buffer,"          ldi   [%s]+1.1                ; Get variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
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
        sprintf(buffer,"          ldi   [%s]+3.1                  ; Get first variable address +3", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   [%s]+3.1                  ; Get second variable address +3", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   [%s]+3.0", matches[2]); Asm(buffer);
        Asm("          plo   rd");
        }
      else {
        sprintf(buffer,"          ldi   [%s]+1.1                  ; Get first variable address +1", matches[0]); Asm(buffer);
        Asm("          phi   rf");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
        Asm("          plo   rf");
        addr = getVariable(matches[2]) + 1;
        sprintf(buffer,"          ldi   [%s]+1.1                  ; Get second variable address +1", matches[2]); Asm(buffer);
        Asm("          phi   rd");
        sprintf(buffer,"          ldi   [%s]+1.0", matches[2]); Asm(buffer);
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
  if (*line != '=') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  line = trim(line);
  line = cexpr(line);
  addr = getVariable(varname);
  if (use32Bits) {
    sprintf(buffer,"          ldi   [%s]+3.1                ; Get destination variable address", varname); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s]+3.0", varname); Asm(buffer);
    Asm("          plo   rf");
    }
  else  {
    sprintf(buffer,"          ldi   [%s]+1.1                ; Get destination variable address", varname); Asm(buffer);
    Asm("          phi   rf");
    sprintf(buffer,"          ldi   [%s]+1.0", varname); Asm(buffer);
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
  while (*line != 0) line++;
  return line;
  }

