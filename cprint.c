#include "header.h"

char* cprint(char* line) {
  char qt;
  char last;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  last = ' ';
  while (*line != ':' && *line != 0) {
    line=trim(line);
    if (*line == '"') {
      output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
      line++;
      while (*line != '"' && *line != 0) {
        output(*line++);
        }
      output(0);
      if (*line == '"') line++;
      last = ' ';
      }
    else if (*line == ',') {
      output(LDI); output(0x09);
      output(SEP+R4); output(lblF_type/256); output(lblF_type%256);
      line++;
      last = ',';
      }
    else if (*line == ';') {
      line++;
      last = ';';
      }
    else {
      line = cexpr(line);
      output(SEP+R4); output(lblItoA/256); output(lblItoA%256);
      last = ' ';
      }
    }
  if (last != ';' && last != ',') {
    output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
    output(10); output(13); output(0);
    }
  return line;
  }

