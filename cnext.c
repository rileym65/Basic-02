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
    output(SEP+R4); output(lblNext/256); output(lblNext%256);
    if (useAsm) {
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Call NEXT handler");
      sprintf(buffer,"          dw    next"); writeAsm(buffer,"");
      }
    }
  else {
    output(LDI); output(addr/256); output(PHI+RC);
    output(LDI); output(addr%256); output(PLO+RC);
    output(SEP+R4); output(lblNextVar/256); output(lblNextVar%256);
    if (useAsm) {
      sprintf(buffer,"          ldi   %s.1",varname); writeAsm(buffer,"Get loop variable address");
      sprintf(buffer,"          phi   rc"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.0",varname); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rc"); writeAsm(buffer,"");
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Call NEXT with var handler");
      sprintf(buffer,"          dw    nextvar"); writeAsm(buffer,"");
      }
    }

  return line;
  }

