#include "header.h"

char* clocate(char* line) {
  int  pos;
  word addr;
  output(SEP+R4); output(lblF_inmsg/256); output(lblF_inmsg%256);
  output(27); output('['); output(0);
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  output(SEP+R4); output(lblItoA/256); output(lblItoA%256);
  output(LDI); output(';');
  output(SEP+R4); output(lblF_type/256); output(lblF_type%256);
  if (useAsm) {
    sprintf(buffer,"          ghi   rc"); writeAsm(buffer,"Get poke address");
    sprintf(buffer,"          stxd"); writeAsm(buffer,"Save on the stack");
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"");
    sprintf(buffer,"          stxd"); writeAsm(buffer,"");
    }
  line = cexpr(line);
  output(SEP+R4); output(lblItoA/256); output(lblItoA%256);
  output(LDI); output('H');
  output(SEP+R4); output(lblF_type/256); output(lblF_type%256);
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

