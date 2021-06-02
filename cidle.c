#include "header.h"

char* cidle(char* line) {
  output(IDL);
  if (useAsm) {
    sprintf(buffer,"          idl"); writeAsm(buffer,"Idle the CPU");
    }
  return line;
  }

