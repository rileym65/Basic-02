#include "header.h"

// On stack:  endValue stepValue varAddr execAddr  scall

char* cfor(char* line) {
  int  pos;
  word vaddr;
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
  vaddr = getVariable(varname);
  output(LDI); output(vaddr/256);
  output(PHI+RF);
  output(LDI); output(vaddr%256);
  output(PLO+RF);
  output(GHI+RC);
  output(STR+RF);
  output(INC+RF);
  output(GLO+RC);
  output(STR+RF);

  if (strncasecmp(line,"to",2) != 0) {
    showError("Syntax error");
    exit(1);
    }
  line += 2;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  output(INC+RC);
  output(GHI+RC); output(STXD);
  output(GLO+RC); output(STXD);

  if (*line == ':' || *line == 0) {
    output(LDI); output(0); output(STXD);
    output(LDI); output(1); output(STXD);
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
    output(GHI+RC); output(STXD);
    output(GLO+RC); output(STXD);
    }
  else {
    showError("Syntax error");
    exit(1);
    }

  addr = address + 12;

  output(LDI); output(vaddr/256); output(STXD);
  output(LDI); output(vaddr%256); output(STXD);

  output(LDI); output(addr/256); output(STXD);
  output(LDI); output(addr%256); output(STXD);

  return line;
  }

