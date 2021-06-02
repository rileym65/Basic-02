#include "header.h"

char* ccls(char* line) {
  line = trim(line);
  if (*line != ':' && *line != 0) {
    showError("Syntax error");
    exit(1);
    }
  output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
  output(27); output('['); output('2'); output('J'); output(0);
  if (useAsm) {
    sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Display message");
    sprintf(buffer,"          dw    f_inmsg"); writeAsm(buffer,"");
    sprintf(buffer,"          db    27,'[2J',0"); writeAsm(buffer,"");
    }
  return line;
  }

