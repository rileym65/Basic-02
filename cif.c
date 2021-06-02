#include "header.h"

char* cif(char* line) {
  word addr;
  line = trim(line);
  line = cexpr(line);
  line = trim(line);
  output(GLO+RC);
  addr = address + 7;
  output(LBNZ); output(addr/256); output(addr%256);
  if (useAsm) {
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"Check result of compare");
    sprintf(buffer,"          lbnz  $+7"); writeAsm(buffer,"Jump if successful");
    }
  if (findNextLine(lastLineNumber, &addr) != 0) {
    showError("Line number not found");
    exit(1);
    }
  output(GHI+RC);
  output(LBZ); output(addr/256); output(addr%256);
  if (strncasecmp(line,"then",4) == 0) {
    line += 4;
    }
  if (useAsm) {
    findNextLineNumber(lastLineNumber, &addr);
    sprintf(buffer,"          ghi   rc"); writeAsm(buffer,"Check high result of compare");
    sprintf(buffer,"          lbz   l%d",addr); writeAsm(buffer,"Jump if fail");
    }
  line = trim(line);
  line--;
  *line = ':';
  return line;
  }

