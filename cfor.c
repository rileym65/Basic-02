#include "header.h"

// On stack:  endValue stepValue varAddr execAddr  scall

char* cfor(char* line) {
  int  pos;
  word vaddr;
  word addr;
  word value;
  char varname[256];
  line = trim(line);
  if (match(line,"A=#A#A#")) {
    if (strcasecmp(matches[3],"to") == 0 && strcasecmp(matches[5],"step") == 0) {
      vaddr = getVariable(matches[0]);
      value = atoi(matches[2]);
      sprintf(buffer,"          ldi   [%s].1                  ; Get variable address",matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
      Asm("          plo   rf");
      sprintf(buffer,"          ldi   %d                      ; Write start to variable",value/256); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          str   rf");
      value = atoi(matches[4])+1;
      sprintf(buffer,"          ldi   %d                      ; Write end value to stack",value/256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          stxd");
      value = atoi(matches[6]);
      sprintf(buffer,"          ldi   %d                      ; Write step value to stack",value/256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   [%s].1                  ; Write variable address to stack",matches[0]); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
      Asm("          stxd");
      addr = address + 6;
      Asm("          ldi   $+6.1                   ; Write execution address to stack");
      Asm("          stxd");
      Asm("          ldi   $+3.0");
      Asm("          stxd");
      while (*line != ':' && *line != 0) line++;
      return line;
      }
    }
  if (match(line,"A=#A#")) {
    if (strcasecmp(matches[3],"to") == 0) {
      vaddr = getVariable(matches[0]);
      value = atoi(matches[2]);
      sprintf(buffer,"          ldi   [%s].1                  ; Get variable address",matches[0]); Asm(buffer);
      Asm("          phi   rf");
      sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
      Asm("          plo   rf");
      sprintf(buffer,"          ldi   %d                      ; Write start to variable",value/256); Asm(buffer);
      Asm("          str   rf");
      Asm("          inc   rf");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          str   rf");
      value = atoi(matches[4])+1;
      sprintf(buffer,"          ldi   %d                      ; Write end value to stack",value/256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          stxd");
      value = 1;
      sprintf(buffer,"          ldi   %d                      ; Write step value to stack",value/256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   %d",value%256); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   [%s].1                  ; Write variable address to stack",matches[0]); Asm(buffer);
      Asm("          stxd");
      sprintf(buffer,"          ldi   [%s].0",matches[0]); Asm(buffer);
      Asm("          stxd");
      addr = address + 6;
      Asm("          ldi   $+6.1                   ; Write execution address to stack");
      Asm("          stxd");
      Asm("          ldi   $+3.0");
      Asm("          stxd");
      while (*line != ':' && *line != 0) line++;
      return line;
      }
    }
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
  vaddr = getVariable(varname);

  sprintf(buffer,"          ldi   [%s].1                  ; Get variable address",varname); Asm(buffer);
  Asm("          phi   rf");
  sprintf(buffer,"          ldi   [%s].0",varname); Asm(buffer);
  Asm("          plo   rf");
  Asm("          ghi   rc                      ; Store start value into variable");
  Asm("          str   rf");
  Asm("          inc   rf");
  Asm("          glo   rc");
  Asm("          str   rf");

  if (strncasecmp(line,"to",2) != 0) {
    showError("Syntax error");
    exit(1);
    }
  line += 2;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  Asm("          inc   rc                      ; End value is 1 higher");
  Asm("          ghi   rc                      ; Store onto stack");
  Asm("          stxd");
  Asm("          glo   rc");
  Asm("          stxd");

  if (*line == ':' || *line == 0) {
    Asm("          ldi   0                       ; No step, so increment is 1");
    Asm("          stxd");
    Asm("          ldi   1");
    Asm("          stxd");
    }
  else if (strncasecmp(line,"step",4) == 0) {
    line += 4;
    line = trim(line);
    line = cexpr(line);
    line = trim(line);
    if (*line != ':' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    Asm("          ghi   rc                      ; Store increment onto stack");
    Asm("          stxd");
    Asm("          glo   rc");
    Asm("          stxd");
    }
  else {
    showError("Syntax error");
    exit(1);
    }

  addr = address + 12;

  sprintf(buffer,"          ldi   [%s].1                  ; Write variable address to stack",varname); Asm(buffer);
  Asm("          stxd");
  sprintf(buffer,"          ldi   [%s].0",varname); Asm(buffer);
  Asm("          stxd");
  addr = address + 6;
  Asm("          ldi   $+6.1                   ; Write execution address to stack");
  Asm("          stxd");
  Asm("          ldi   $+3.0");
  Asm("          stxd");

  return line;
  }

