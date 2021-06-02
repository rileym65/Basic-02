#include "header.h"

char* cioff(char* line) {
  word target;
  target = address;
  output(SEX+R3);
  output(DIS); output(0x23);
  if (useAsm) {
    sprintf(buffer,"          sex   r3"); writeAsm(buffer,"Set X=P");
    sprintf(buffer,"          dis"); writeAsm(buffer,"Turn interrupts off");
    sprintf(buffer,"          db    023h"); writeAsm(buffer,"");
    }
  return line;
  }

