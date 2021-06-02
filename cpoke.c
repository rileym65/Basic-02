#include "header.h"

char* cpoke(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  output(GHI+RC);
  output(STXD);
  output(GLO+RC);
  output(STXD);
  if (useAsm) {
    sprintf(buffer,"          ghi   rc"); writeAsm(buffer,"Get poke address");
    sprintf(buffer,"          stxd"); writeAsm(buffer,"Save on the stack");
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"");
    sprintf(buffer,"          stxd"); writeAsm(buffer,"");
    }
  line = cexpr(line);
  output(IRX);
  output(LDXA);
  output(PLO+RF);
  output(LDX);
  output(PHI+RF);
  output(GLO+RC);
  output(STR+RF);
  if (useAsm) {
    sprintf(buffer,"          irx"); writeAsm(buffer,"Recover poke address");
    sprintf(buffer,"          ldxa"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          ldx"); writeAsm(buffer,"");
    sprintf(buffer,"          phi   rf"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   rc"); writeAsm(buffer,"Get low byte of poke value");
    sprintf(buffer,"          str   rf"); writeAsm(buffer,"And write it to memory");
    }
  return line;
  }

