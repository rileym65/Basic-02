#include "header.h"

char* cq(char* line) {
  word addr;
  line = trim(line);
  if (match(line,"#")) {
    if (atoi(line) > 0) {
      output(SEQ);
      if (useAsm) {
        sprintf(buffer,"          seq"); writeAsm(buffer,"Turn on Q");
        }
      }
    else {
      output(REQ);
      if (useAsm) {
        sprintf(buffer,"          req"); writeAsm(buffer,"Turn off Q");
        }
      }
    while (*line != ':' && *line != 0) line++;
    return line;
    }
  line = cexpr(line);
  output(GLO+RC);
  if (useAsm) {
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"Recover computed value");
    }
  addr = address + 7;
  output(LBZ); output(addr/256); output(addr%256);
  output(REQ);
  if (useAsm) {
    sprintf(buffer,"          lbz   $+7"); writeAsm(buffer,"Jump if non-zero");
    sprintf(buffer,"          req"); writeAsm(buffer,"Turn off Q");
    }
  addr = address + 4;
  output(LBR); output(addr/256); output(addr%256);
  output(SEQ);
  if (useAsm) {
    sprintf(buffer,"          lbr   $+4"); writeAsm(buffer,"Move past SEQ");
    sprintf(buffer,"          seq"); writeAsm(buffer,"Turn on Q");
    }
  return line;
  }

