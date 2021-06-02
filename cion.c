#include "header.h"

char* cion(char* line) {
  word target;
  target = address;
  output(SEX+R3);
  output(RET); output(0x23);
  if (useAsm) {
    sprintf(buffer,"          sex   r3"); writeAsm(buffer,"Set X=P");
    sprintf(buffer,"          ret"); writeAsm(buffer,"Turn interrupts on");
    sprintf(buffer,"          db    023h"); writeAsm(buffer,"");
    }
  return line;
  }

