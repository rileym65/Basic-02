#include "header.h"

char* creturn(char* line) {
  word target;
  output(SEP+R5);
  if (useAsm) {
    sprintf(buffer,"          sep   sret"); writeAsm(buffer,"Return");
    }
  return line;
  }

