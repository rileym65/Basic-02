#include "header.h"

char* cend(char* line) {
  word target;
  target = address;
  if (useStg) {
    Asm("            ldi  [STG_].1");
    Asm("            phi  rf");
    Asm("            ldi  [STG_].0");
    Asm("            plo  rf");
    Asm("            lda  rf");
    Asm("            phi  r2");
    Asm("            ldn  rf");
    Asm("            plo  r2");
    Asm("            sex  r2");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            plo  r6");
    Asm("            ldx");
    Asm("            phi  r6");
    Asm("            sep  sret");
    }
  else if (exitAddress != 0xffff) {
    output(LBR); output(exitAddress / 256); output(exitAddress % 256);
    }
  else if (useElfos) {
    target = 0x303;
    output(LBR); output(target / 256); output(target % 256);
    }
  else {
    output(IDL);
    output(LBR); output(target / 256); output(target % 256);
    if (useAsm) {
      sprintf(buffer,"lend:     idl"); writeAsm(buffer,"Idle the CPU");
      sprintf(buffer,"          lbr   lend",matches[0]); writeAsm(buffer,"");
      }
    }
  return line;
  }

