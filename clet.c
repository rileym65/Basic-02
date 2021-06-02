#include "header.h"

char* clet(char* line) {
  int  pos;
  word addr;
  word value;
  char varname[256];
  line = trim(line);
  /* ********************************** */
  /* ***** Look for optimizations ***** */
  /* ********************************** */
  if (match(line,"A=#")) {
    addr = getVariable(matches[0]);
    value = atoi(matches[2]);
    output(LDI); output(addr/256);
    output(PHI+RF);
    output(LDI); output(addr%256);
    output(PLO+RF);
    output(LDI); output(value/256);
    output(STR+RF); output(INC+RF);
    output(LDI); output(value%256);
    output(STR+RF);
    if (useAsm) {
      sprintf(buffer,"          ldi   %s.1",matches[0]); writeAsm(buffer,"Get variable address");
      sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.0",matches[0]); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %d",value/256); writeAsm(buffer,"Write value to variable");
      sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          inc   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %d",value%256); writeAsm(buffer,"");
      sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
      }
    while (*line != 0 && *line != ':') line++;
    return line;
    }
  if (match(line,"A=A")) {
    addr = getVariable(matches[0]);
    output(LDI); output(addr/256);
    output(PHI+RF);
    output(LDI); output(addr%256);
    output(PLO+RF);
    addr = getVariable(matches[2]);
    output(LDI); output(addr/256);
    output(PHI+RD);
    output(LDI); output(addr%256);
    output(PLO+RD);
    output(LDA+RD); output(STR+RF); output(INC+RF);
    output(LDN+RD); output(STR+RF);
    if (useAsm) {
      sprintf(buffer,"          ldi   %s.1",matches[0]); writeAsm(buffer,"Get first variable address");
      sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.0",matches[0]); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.1",matches[2]); writeAsm(buffer,"Get second variable address");
      sprintf(buffer,"          phi   rd"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.0",matches[2]); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rd"); writeAsm(buffer,"");
      sprintf(buffer,"          lda   rd"); writeAsm(buffer,"Transfer value");
      sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          inc   rf"); writeAsm(buffer,"");
      sprintf(buffer,"          ldn   rd"); writeAsm(buffer,"");
      sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
      }
    while (*line != 0 && *line != ':') line++;
    return line;
    }
  if (match(line,"A=A+#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      output(LDI); output(addr/256);
      output(PHI+RF);
      output(LDI); output(addr%256);
      output(PLO+RF);
      output(LDN+RF); output(ADI); output(value%256);
      output(STR+RF); output(DEC+RF);
      output(LDN+RF); output(ADCI); output(value/256);
      output(STR+RF);
      if (useAsm) {
        sprintf(buffer,"          ldi   (%s+1).1",matches[0]); writeAsm(buffer,"Get variable address +1");
        sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          ldi   (%s+1).0",matches[0]); writeAsm(buffer,"");
        sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          ldn   rf"); writeAsm(buffer,"Add in constant value");
        sprintf(buffer,"          adi   %d",value%256); writeAsm(buffer,"");
        sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          dec   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          ldn   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          adci  %d",value/256); writeAsm(buffer,"");
        sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      output(LDI); output(addr/256);
      output(PHI+RF);
      output(LDI); output(addr%256);
      output(PLO+RF);
      addr = getVariable(matches[2]) + 1;
      output(LDI); output(addr/256);
      output(PHI+RD);
      output(LDI); output(addr%256);
      output(PLO+RD);
      output(LDN+RD); output(ADI); output(value%256);
      output(STR+RF); output(DEC+RF); output(DEC+RD);
      output(LDN+RD); output(ADCI); output(value/256);
      output(STR+RF);
      if (useAsm) {
        sprintf(buffer,"          ldi   (%s+1).1",matches[0]); writeAsm(buffer,"Get first variable address +1");
        sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          ldi   (%s+1).0",matches[0]); writeAsm(buffer,"");
        sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          ldi   (%s+1).1",matches[2]); writeAsm(buffer,"Get second variable address +1");
        sprintf(buffer,"          phi   rd"); writeAsm(buffer,"");
        sprintf(buffer,"          ldi   (%s+1).0",matches[2]); writeAsm(buffer,"");
        sprintf(buffer,"          plo   rd"); writeAsm(buffer,"");
        sprintf(buffer,"          ldn   rd"); writeAsm(buffer, "Add constant and second variable");
        sprintf(buffer,"          adi   %d",value%256); writeAsm(buffer,"");
        sprintf(buffer,"          str   rf"); writeAsm(buffer,"and store into first variable");
        sprintf(buffer,"          dec   rf"); writeAsm(buffer,"");
        sprintf(buffer,"          dec   rd"); writeAsm(buffer,"");
        sprintf(buffer,"          ldn   rd"); writeAsm(buffer, "");
        sprintf(buffer,"          adci  %d",value/256); writeAsm(buffer,"");
        sprintf(buffer,"          str   rf"); writeAsm(buffer,"");
        }
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    }
  if (match(line,"A=A-#")) {
    if (strcasecmp(matches[0], matches[2]) == 0) {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      output(LDI); output(addr/256);
      output(PHI+RF);
      output(LDI); output(addr%256);
      output(PLO+RF);
      output(LDN+RF); output(SMI); output(value%256);
      output(STR+RF); output(DEC+RF);
      output(LDN+RF); output(SMBI); output(value/256);
      output(STR+RF);
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    else {
      addr = getVariable(matches[0]) + 1;
      value = atoi(matches[4]);
      output(LDI); output(addr/256);
      output(PHI+RF);
      output(LDI); output(addr%256);
      output(PLO+RF);
      addr = getVariable(matches[2]) + 1;
      output(LDI); output(addr/256);
      output(PHI+RD);
      output(LDI); output(addr%256);
      output(PLO+RD);
      output(LDN+RD); output(SMI); output(value%256);
      output(STR+RF); output(DEC+RF); output(DEC+RD);
      output(LDN+RD); output(SMBI); output(value/256);
      output(STR+RF);
      while (*line != 0 && *line != ':') line++;
      return line;
      }
    }
  /* ********************************** */
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
  if (useAsm) {
    sprintf(buffer,"          ldi   %s.1",varname); writeAsm(buffer,"Get destination variable address");
    sprintf(buffer,"          phi   rf"); writeAsm(buffer, "");
    sprintf(buffer,"          ldi   %s.0",varname); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rf"); writeAsm(buffer, "");
    sprintf(buffer,"          ghi   rc"); writeAsm(buffer, "Write expr result to variable");
    sprintf(buffer,"          str   rf"); writeAsm(buffer, "");
    sprintf(buffer,"          inc   rf"); writeAsm(buffer, "");
    sprintf(buffer,"          glo   rc"); writeAsm(buffer, "");
    sprintf(buffer,"          str   rf"); writeAsm(buffer, "");
    }

  while (*line != 0) line++;

  return line;
  }

