#include "header.h"

char* clet(char* line) {
  int  pos;
  word addr;
  char varname[256];
  line = trim(line);
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
  output(LDI); output(addr/256);
  output(PHI+RF);
  output(LDI); output(addr%256);
  output(PLO+RF);
  output(GHI+RC);
  output(STR+RF);
  output(INC+RF);
  output(GLO+RC);
  output(STR+RF);

  while (*line != 0) line++;

  return line;
  }

