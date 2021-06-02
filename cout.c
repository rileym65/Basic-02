#include "header.h"

char* cout(char* line) {
  int  pos;
  word addr;
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  output(LDI); output(SEP+R3);
  output(STXD);
  output(GLO+RC);
  output(ANI); output(7);
  output(ORI); output(0x60);
  output(STXD);
  if (useAsm) {
    sprintf(buffer,"          ldi   0d3h"); writeAsm(buffer,"Need a SEP R3 command");
    sprintf(buffer,"          stxd"); writeAsm(buffer, "Place on stack");
    sprintf(buffer,"          glo   rc"); writeAsm(buffer, "Get port");
    sprintf(buffer,"          ani   7"); writeAsm(buffer, "Keep only bottom 3 bits");
    sprintf(buffer,"          ori   060h"); writeAsm(buffer, "Convert to OUT command");
    sprintf(buffer,"          stxd"); writeAsm(buffer, "Place on stack");
    }
  line = cexpr(line);
  output(IRX);
  output(LDX);
  output(PLO+RE);
  output(GLO+RC);
  output(STXD);
  output(GLO+RE);
  output(STR+R2);
  output(SEP+R2);
  output(DEC+R2);
  if (useAsm) {
    sprintf(buffer,"          irx"); writeAsm(buffer,"Recover OUT command");
    sprintf(buffer,"          ldx"); writeAsm(buffer,"");
    sprintf(buffer,"          plo   re"); writeAsm(buffer, "Set aside for a moment");
    sprintf(buffer,"          glo   rc"); writeAsm(buffer, "Write output value to stack");
    sprintf(buffer,"          stxd"); writeAsm(buffer, "");
    sprintf(buffer,"          glo   re"); writeAsm(buffer, "Recover OUT command");
    sprintf(buffer,"          str   r2"); writeAsm(buffer, "Place back on stack");
    sprintf(buffer,"          sep   r2"); writeAsm(buffer, "Execute code on stack");
    sprintf(buffer,"          dec   r2"); writeAsm(buffer, "Put stack point back were it belongs");
    }
  return line;
  }

