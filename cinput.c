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
    if (useAsm) {
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Display message");
      sprintf(buffer,"          dw    f_inmsg"); writeAsm(buffer,"");
      strcpy(buffer,"          db    '");
      }
    line++;
    while (*line != '"' && *line != 0) {
      if (useAsm) {
        buffer[strlen(buffer)+1] = 0;
        buffer[strlen(buffer)] = *line;
        }
      output(*line++);
      }
    if (*line == '"') line++;
    output(0);
    if (useAsm) {
      strcat(buffer,"',0"); writeAsm(buffer,"");
      }
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
    if (useAsm) {
      sprintf(buffer,"          ldi   keybuf.1"); writeAsm(buffer,"Point to keyboard buffer");
      sprintf(buffer,"          phi   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          ldi   keybuf.0"); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Get input from user");
      sprintf(buffer,"          dw    f_input"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   keybuf.1"); writeAsm(buffer,"Point to keyboard buffer");
      sprintf(buffer,"          phi   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          ldi   keybuf.0"); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Convert ASCII to integer");
      sprintf(buffer,"          dw    atoi"); writeAsm(buffer,"");
      sprintf(buffer,"          ldi   %s.1",name); writeAsm(buffer,"Point to destination variable");
      sprintf(buffer,"          phi   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          ldi   %s.0",name); writeAsm(buffer,"");
      sprintf(buffer,"          plo   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          ghi   rc"); writeAsm(buffer,"Store value into variable");
      sprintf(buffer,"          str   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          inc   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          glo   rc"); writeAsm(buffer,"");
      sprintf(buffer,"          str   rf"); writeAsm(buffer, "");
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Display cr/lf");
      sprintf(buffer,"          dw    f_inmsg"); writeAsm(buffer,"");
      sprintf(buffer,"          db    10,13,0"); writeAsm(buffer,"");
      }

    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') line++;
    }
  return line;
  }

