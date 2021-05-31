#include "header.h"

char* cinput(char* line) {
  char qt;
  word addr;
  char name[256];
  int  pos;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  if (*line = '"') {
    output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
    line++;
    while (*line != '"' && *line != 0) {
      output(*line++);
      }
    if (*line == '"') line++;
    output(0);
    line = trim(line);
    if (*line != ',') {
      showError("Syntax error");
      exit(1);
      }
    }
  line++;
  while (*line != ':' && *line != 0) {
    if (!(*line >= 'a' && *line <= 'z') &&
        !(*line >= 'A' && *line <= 'Z')) {
      showError("Syntax error");
      exit(1);
      }
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') {
      name[pos++] = *line++;
      }
    name[pos] = 0;
    if (strlen(name) == 0) {
      showError("Syntax error");
      exit(1);
      }
    addr = getVariable(name);
    output(LDI); output(variableRAM/256); output(PHI+RF);
    output(LDI); output(variableRAM%256); output(PLO+RF);
    output(SEP+R4); output(lblF_input/256); output(lblF_input%256);
    output(LDI); output(variableRAM/256); output(PHI+RF);
    output(LDI); output(variableRAM%256); output(PLO+RF);
    output(SEP+R4); output(lblAtoI/256); output(lblAtoI%256);
    output(LDI); output(addr/256); output(PHI+RF);
    output(LDI); output(addr%256); output(PLO+RF);
    output(GHI+RC); output(STR+RF); output(INC+RF);
    output(GLO+RC); output(STR+RF);
    output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
    output(10); output(13); output(0);
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') line++;
    }
  return line;
  }

