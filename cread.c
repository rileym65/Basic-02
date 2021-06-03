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
  if (useAsm) {
    sprintf(buffer,"          ldi   DATA_.1"); writeAsm(buffer,"Point to DATA pointer");
    sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ldi   DATA_.0"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          lda   rf"); writeAsm(buffer,"Retrieve DATA pointer");
    sprintf(buffer,"          phi   rd"); writeAsm(buffer,"");
    sprintf(buffer,"          ldn   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rd"); writeAsm(buffer,"");
    }
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
      if (useAsm) {
        sprintf(buffer,"          ldi   %s.1",token); writeAsm(buffer,"Point to variable");
        sprintf(buffer,"          phi   rc"); writeAsm(buffer,"");
        }
      }
    output(LDI); output(addr%256); output(PLO+RC);
    output(LDA+RD); output(STR+RC); output(INC+RC);
    output(LDA+RD); output(STR+RC);
    if (useAsm) {
      sprintf(buffer,"          ldi   %s.0",token); writeAsm(buffer,"Point to variable");
      sprintf(buffer,"          plo   rc"); writeAsm(buffer,"");
      sprintf(buffer,"          lda   rd"); writeAsm(buffer,"Retrieve data from DATA pool");
      sprintf(buffer,"          str   rc"); writeAsm(buffer,"And store into variable");
      sprintf(buffer,"          inc   rc"); writeAsm(buffer,"");
      sprintf(buffer,"          lda   rd"); writeAsm(buffer,"");
      sprintf(buffer,"          str   rc"); writeAsm(buffer,"");
      }
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
  if (useAsm) {
    sprintf(buffer,"          glo   rd"); writeAsm(buffer,"Save DATA pointer");
    sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          dec   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ghi   rd"); writeAsm(buffer,"");
    sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
    }
  return line;
  }

