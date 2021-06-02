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
      output(0);
      if (useAsm) {
        strcat(buffer,"',0"); writeAsm(buffer,"");
        }
      if (*line == '"') line++;
      last = ' ';
      }
    else if (*line == ',') {
      output(LDI); output(0x09);
      output(SEP+R4); output(lblF_type/256); output(lblF_type%256);
      line++;
      last = ',';
      if (useAsm) {
        sprintf(buffer,"          ldi   9"); writeAsm(buffer,"Display a tab character");
        sprintf(buffer,"          sep   scall"); writeAsm(buffer,"");
        sprintf(buffer,"          dw    f_type"); writeAsm(buffer,"");
        }
      }
    else if (*line == ';') {
      line++;
      last = ';';
      }
    else {
      line = cexpr(line);
      output(SEP+R4); output(lblItoA/256); output(lblItoA%256);
      if (useAsm) {
        sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Display integer value");
        sprintf(buffer,"          dw    itoa"); writeAsm(buffer,"");
        }
      last = ' ';
      }
    }
  if (last != ';' && last != ',') {
    output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
    output(10); output(13); output(0);
    if (useAsm) {
      sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Display cr/lf");
      sprintf(buffer,"          dw    f_inmsg"); writeAsm(buffer,"");
      sprintf(buffer,"          db    10,13,0"); writeAsm(buffer,"");
      }

    }
  return line;
  }

