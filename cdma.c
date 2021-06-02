#include "header.h"

char* cdma(char* line) {
  word target;
  line = trim(line);
  line = cexpr(line);
  output(GLO+RC);
  output(PLO+R0);
  output(GHI+RC);
  output(PHI+R0);
  if (useAsm) {
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"Set R0 to address");
    sprintf(buffer,"          plo   r0"); writeAsm(buffer,"");
    sprintf(buffer,"          ghi   rc"); writeAsm(buffer,"");
    sprintf(buffer,"          phi   r0"); writeAsm(buffer,"");
    }

  return line;
  }

