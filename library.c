/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "header.h"
#include "library.h"

// R7 - data stack

void library() {
  int  i;
  char ctmp;
  word t1,t2,t3;
  FILE* file;
  ctmp = showCompiler;
  showCompiler = 0;
  Asm("scall:      equ  r4");
  Asm("sret:       equ  r5");
  if (useElfos == 0) {
    sprintf(buffer,"stack:      equ  0%04xh",stack); Asm(buffer);
    sprintf(buffer,"estack:     equ  0%04xh",estack); Asm(buffer);
    }
  if (useElfos) {
    t1 = programStart;
    t2 = (highest - programStart + 1);
    t3 = programStart;
    sprintf(buffer,"          dw   %d,%d,%d",t1,t2,t3); Asm(buffer);
    }
  if (useElfos || useStg) {
    Asm("init:       lbr  start");
    }
  else {
    Asm("init:       sex  r0");
    Asm("            dis");
    Asm("            db   020h");
    Asm("            ldi  start.1");
    Asm("            phi  r3");
    Asm("            ldi  start.0");
    Asm("            plo  r3");
    }
  Asm("            sep  r3");
  Asm("call:       plo     re");
  Asm("            ghi     r6");
  Asm("            stxd");
  Asm("            glo     r6");
  Asm("            stxd");
  Asm("            ghi     r3");
  Asm("            phi     r6");
  Asm("            glo     r3");
  Asm("            plo     r6");
  Asm("            lda     r6");
  Asm("            phi     r3");
  Asm("            lda     r6");
  Asm("            plo     r3");
  Asm("            glo     re");
  Asm("            br      call-1");
  Asm("            sep     r3");
  Asm("ret:        plo     re");
  Asm("            ghi     r6");
  Asm("            phi     r3");
  Asm("            glo     r6");
  Asm("            plo     r3");
  Asm("            irx");
  Asm("            ldxa");
  Asm("            plo     r6");
  Asm("            ldx");
  Asm("            phi     r6");
  Asm("            glo     re");
  Asm("            br      ret-1");
  Asm("return:     sep  sret");

  file = fopen("library.asm","r");
  if (file == NULL) {
    i = 0;
    while (strstr(librarysrc[i],"__END__") == NULL) {
      Asm(librarysrc[i]);
      i++;
      }
    }
  else {
    fclose(file);
    Asm("#include library.asm");
    }


  if (passNumber == 1) lblStart = address;
  if (useElfos) {
    Asm("start:      ldi  004h");
    Asm("            phi  rf");
    Asm("            ldi  042h");
    Asm("            plo  rf");
    Asm("            lda  rf");
    Asm("            phi  r2");
    Asm("            smi  1");
    Asm("            phi  r7");
    Asm("            lda  rf");
    Asm("            plo  r2");
    Asm("            plo  r7");
    }
  else if (useStg) {
    Asm("start:      ghi  r6");
    Asm("            stxd");
    Asm("            glo  r6");
    Asm("            stxd");
    Asm("            ldi  STG_.1");
    Asm("            phi  rf");
    Asm("            ldi  STG_.0");
    Asm("            plo  rf");
    Asm("            ghi  r2");
    Asm("            str  rf");
    Asm("            inc  rf");
    Asm("            glo  r2");
    Asm("            str  rf");
    }
  else {
    Asm("start:      ldi  stack.1");
    Asm("            phi  r2");
    Asm("            ldi  stack.0");
    Asm("            plo  r2");
    }
  if (useElfos == 0) {
    Asm("            ldi  estack.1");
    Asm("            phi  r7");
    Asm("            ldi  estack.0");
    Asm("            plo  r7");
    }
  if (useElfos == 0 && useStg == 0) {
    Asm("          ldi  call.1");
    Asm("          phi  r4      ");
    Asm("          ldi  call.0");
    Asm("          plo  r4");
    Asm("          ldi  ret.1");
    Asm("          phi  r5      ");
    Asm("          ldi  ret.0");
    Asm("          plo  r5");
    }
//   t1 = variableRAM + (2 * numberOfVariables);
  t1 = variableNextAddress;
  Asm("          ldi  free_.1");
  Asm("          phi  rf");
  Asm("          ldi  free_.0");
  Asm("          plo  rf");
  if (use32Bits) {
    Asm("          ldi  0");
    Asm("          str  rf");
    Asm("          inc  rf");
    Asm("          str  rf");
    Asm("          inc  rf");
    }
  Asm("          ldi  END__.1");
  Asm("          str  rf");
  Asm("          inc  rf");
  Asm("          ldi  END__.0");
  Asm("          str  rf");
  if (useData) {
    Asm("          ldi  DATA_.1");
    Asm("          phi  rf");
    Asm("          ldi  DATA_.0");
    Asm("          plo  rf");
    Asm("          ldi  data.1");
    Asm("          str  rf");
    Asm("          inc  rf");
    Asm("          ldi  data.0");
    Asm("          str  rf");
    }
  if (getDefine("HEAP")) {
    Asm("          ldi  HEAP_.1");
    Asm("          phi  rf");
    Asm("          ldi  HEAP_.0");
    Asm("          plo  rf");
    if (useElfos) {
      Asm("          ghi  r7");
      Asm("          smi  1");
      Asm("          str  rf");
      Asm("          phi  r9");
      Asm("          inc  rf");
      Asm("          glo  r7");
      Asm("          plo  r9");
      Asm("          str  rf");
      Asm("          ldi  0");
      Asm("          str  r9");
      }
    else {
      sprintf(buffer,"          ldi  %d",heap/256); Asm(buffer);
      Asm("          str  rf");
      Asm("          inc  rf");
      sprintf(buffer,"          ldi  %d",heap%256); Asm(buffer);
      Asm("          str  rf");
      }
    }
  if ((getDefine("ITOA16") || getDefine("ATOI16") || getDefine("ITOA32") || getDefine("ATOI32")) && useElfos == 0) {
    Asm("          sep  scall");
    Asm("          dw   f_setbd");
    }
  showCompiler = ctmp;
  if (passNumber == 1) runtime = address;
  }

