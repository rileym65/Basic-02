#include "header.h"

char* cread(char* line) {
  word last;
  int  pos;
  word addr;
  word num;
  char neg;
  char token[128];
  last = 0xffff;
  line = trim(line);
  addr = getVariable("DATA_");
  output(LDI); output(addr/256); output(PHI+RF);
  output(LDI); output(addr%256); output(PLO+RF);
  output(LDA+RF); output(PHI+RD);
  output(LDN+RF); output(PLO+RD);
  while (*line != ':' && *line != 0) {
    if ((*line < 'a' || *line > 'z') &&
        (*line < 'A' || *line > 'Z')) {
      showError("Syntax error");
      exit(1);
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
            *line == '_') {
      token[pos++] = *line;
      token[pos] = 0;
      line++;
      }
    addr = getVariable(token);
    if (last == 0xffff || ((addr & 0xff00) != (addr & 0xff00))) {
      output(LDI); output(addr/256); output(PHI+RC);
      }
    output(LDI); output(addr%256); output(PLO+RC);
    output(LDA+RD); output(STR+RC); output(INC+RC);
    output(LDA+RD); output(STR+RC);
    last = addr;
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') {
      line++;
      line = trim(line);
      }
    }
  output(GLO+RD); output(STR+RF); output(DEC+RF);
  output(GHI+RD); output(STR+RF);
  return line;
  }

