#include "header.h"

char* clet(char* line) {
  int  pos;
  word addr;
  word value;
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
    sprintf(buffer,"          ldi   %d                      ; Write value to variable", value/256); Asm(buffer);
    Asm("          str   rf");
    Asm("          inc   rf");
    sprintf(buffer,"          ldi   %d", value%256); Asm(buffer);
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
    Asm("          ldn   rd                      ; Transfer value");
    Asm("          str   rf");
    while (*line != 0 && *line != ':') line++;
    return line;
    }
  if (match(line,"A=A+#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      sprintf(buffer,"          ldi   [%s]+1.1                ; Get variable address +1", matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
      Asm("          plo   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          adi   %d                      ; Add in constant value", value%256); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          adci  %d", value/256); Asm(buffer);
      Asm("          str   rf");
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      sprintf(buffer,"          ldi   [%s]+1.1                  ; Get first variable address +1", matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
      Asm("          plo   rf");
      addr = getVariable(matches[2]) + 1;
      sprintf(buffer,"          ldi   [%s]+1.1                  ; Get second variable address +1", matches[2]); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[2]); Asm(buffer);
      Asm("          plo   rd");
      Asm("          ldn   rd                      ; Add constant and second variable");
      sprintf(buffer,"          adi   %d                      ; Add in constant value", value%256); Asm(buffer);
      Asm("          str   rf                      ; Add store into first variable");
      Asm("          dec   rf");
      Asm("          dec   rd");
      Asm("          ldn   rd");
      sprintf(buffer,"          adci  %d", value/256); Asm(buffer);
      Asm("          str   rf");
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    }
  if (match(line,"A=A-#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      sprintf(buffer,"          ldi   [%s]+1.1                ; Get variable address +1", matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
      Asm("          plo   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          smi   %d                      ; Subtract constant value", value%256); Asm(buffer);
      Asm("          str   rf");
      Asm("          dec   rf");
      Asm("          ldn   rf");
      sprintf(buffer,"          smbi  %d", value/256); Asm(buffer);
      Asm("          str   rf");
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      sprintf(buffer,"          ldi   [%s]+1.1                  ; Get first variable address +1", matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[0]); Asm(buffer);
      Asm("          plo   rf");
      addr = getVariable(matches[2]) + 1;
      sprintf(buffer,"          ldi   [%s]+1.1                  ; Get second variable address +1", matches[2]); Asm(buffer);
      Asm("          phi   rd");
      sprintf(buffer,"          ldi   [%s]+1.0", matches[2]); Asm(buffer);
      Asm("          plo   rd");
      Asm("          ldn   rd                      ; Add constant and second variable");
      sprintf(buffer,"          smi   %d                      ; Subtract constant value", value%256); Asm(buffer);
      Asm("          str   rf                      ; Add store into first variable");
      Asm("          dec   rf");
      Asm("          dec   rd");
      Asm("          ldn   rd");
      sprintf(buffer,"          smbi  %d", value/256); Asm(buffer);
      Asm("          str   rf");
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
  sprintf(buffer,"          ldi   [%s].1                  ; Get destination variable address", varname); Asm(buffer);
  Asm("          phi   rf");
  sprintf(buffer,"          ldi   [%s].0", varname); Asm(buffer);
  Asm("          plo   rf");
  Asm("          ghi   rc                      ; Write epxressin result to variable");
  Asm("          str   rf");
  Asm("          inc   rf");
  Asm("          glo   rc");
  Asm("          str   rf");
  while (*line != 0) line++;
  return line;
  }

