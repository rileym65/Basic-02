/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void writeAsm(char* line,char* rem) {
  char buffer[256];
  if (passNumber == 1) return;
  if (strlen(rem) > 0) {
    while (strlen(line) < 40) strcat(line," ");
    sprintf(buffer,"%s; %s\n",line,rem);
    if (showAsm) printf("%s",buffer);
    if (useAsm) write(asmFile, buffer, strlen(buffer));
    }
  else {
    sprintf(buffer,"%s\n",line);
    if (showAsm) printf("%s",buffer);
    if (useAsm) write(asmFile, buffer, strlen(buffer));
    }
  }

/*
void writeOutput() {
  int i;
  byte checksum;
  char outLine[80];
  char temp[16];
  if (outMode == 'R') {
    sprintf(outLine,":%04x",outAddress);
    for (i=0; i<outCount; i++) {
      sprintf(temp," %02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'I') {
    checksum = outCount;
    sprintf(outLine,":%02x",outCount);
    checksum += (outAddress / 256);
    checksum += (outAddress & 0xff);
    sprintf(temp,"%04x00",outAddress);
    strcat(outLine,temp);
    for (i=0; i<outCount; i++) {
      checksum += outBuffer[i];
      sprintf(temp,"%02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    checksum = (checksum ^ 0xff) + 1;
    sprintf(temp,"%02x",checksum);
    strcat(outLine, temp);
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'B') {
    write(outFile, outBuffer, outCount);
    }
  }

void output(byte value) {
  if (compMode == 'A' && (address < ramStart || address > ramEnd)) {
    showError("Address exceeded available RAM");
    exit(1);
    }
  if (compMode == 'O' && (address < romStart || address > romEnd)) {
    showError("Address exceeded available ROM");
    exit(1);
    }
  if (passNumber == 1) {
    if (address > highest) highest = address;
    }
  if (passNumber == 2) {
    if (showCompiler) {
      printf(" %02x",value);
      listCount++;
      if (listCount == 16) {
        printf("\n");
        printf("     ");
        listCount = 0;
        }
      }
    outBuffer[outCount++] = value;
    codeGenerated++;
    if (outCount == 16) {
      writeOutput();
      outCount = 0;
      outAddress = address+1;
      }
    }
  address++;
  }
*/

int main(int argc, char** argv, char** envp) {
  int i;
  char temp[1024];
  printf("BASIC/02 Compiler v0.1\n");
  printf("by Michael H. Riley\n");
  printf("\n");
  strcpy(sourceFile,"");
  if (argc < 2) {
    printf("Usage: sbc [options] filename\n");
    exit(1);
    }
  iBufferSize = 0;
  outMode = 'R';
  programStart = 0xffff;
  variableStart = 0xffff;
  exitAddress = 0xffff;
  ramStart = 0x0000;
  ramEnd = 0xffff;
  romStart = 0xffff;
  romEnd = 0xffff;
  showAsm = 0;
  showSymbols = 0;
  showCompiler = 0;
  showList = 0;
  showOptions = 0;
  showVariables = 0;
  showRuntime = 0;
  stack = 0;
  estack = 0;
  heap = 0;
  useSelfTerm = 0;
  useElfos = 0;
  useData = 0;
  useStg = 0;
  useAsm = 0;
  use1805 = 0;
  use32Bits = 0;
  useFp = 0;
  createLst = 0;
  lblF_inmsg = 0xff66;
  lblF_type = 0xff03;
  lblF_read = 0xff06;
  lblF_input = 0xff0f;
  lblF_msg = 0xff09;
  lblF_setbd = 0xff2d;
  strcpy(lineEnding,"\n");
  SERSEQ = SEQ;
  SERREQ = REQ;
  SERN = BN2;
  SERP = B2;
  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-') strcpy(sourceFile,argv[i]);
    }
  strcpy(baseName, sourceFile);
  if (strstr(baseName,".bas") != NULL) {
    *(strstr(baseName,".bas")) = 0;
    }
  for (i=0; envp[i] != NULL; i++) {
    if (strncasecmp(envp[i],"home=",5) == 0) {
      strcpy(temp,envp[i]+5);
      if (temp[strlen(temp)-1] != '/') strcat(temp,"/");
      strcat(temp,".sbc.rc");
      optionFile(temp);
      }
    }
  optionFile("sbc.rc");
  strcpy(temp, baseName);
  strcat(temp, ".rc");
  optionFile(temp);
  i = 1;
  while (i < argc) {
    processOption(argv[i]);
    i++;
    }
  if (strlen(sourceFile) == 0) {
    printf("No source file specified\n");
    exit(1);
    }
  strcpy(outName,baseName);
  switch (outMode) {
    case 'R': strcat(outName, ".prg"); break;
    case 'I': strcat(outName, ".hex"); break;
    case 'B': strcat(outName, ".bin"); break;
    }
  strcpy(asmName,baseName);
  strcat(asmName,".asm");
  strcpy(lstName,baseName);
  strcat(lstName,".lst");
  printf("out: %s\n",outName);
  if (programStart == 0xffff) programStart = 0x0000;
  if (programStart >= ramStart && programStart <= ramEnd) compMode = 'A';
  if (programStart >= romStart && programStart <= romEnd) compMode = 'O';
  if (stack == 0) stack = ramEnd;
  if (estack == 0) estack = stack - 256;
  if (heap == 0) heap = estack - 256;
  if (iBufferSize == 0) iBufferSize = 128;
  if (stack < ramStart || stack > ramEnd) {
    printf("Error: Stack is outside of RAM\n");
    exit(1);
    }
  if (estack < ramStart || estack > ramEnd) {
    printf("Error: Expr Stack is outside of RAM\n");
    exit(1);
    }
  if (variableStart != 0xffff && (variableStart < ramStart || variableStart > ramEnd)) {
    printf("Error: Variable storage is outside of RAM\n");
    exit(1);
    }
  lblStart = 0x0000;
  numberOfLines = 0;
  numberOfVariables = 0;
  numData = 0;
  numDataLines = 0;
  numLabels = 0;
  numDefines = 0;
  numNests = 0;
  codeGenerated = 0;
  highest = 0;
  prepass(sourceFile);
  //grw - moved variable defs before pass 1
  if (getDefine("FILES")) {
    getVariable("IORESULT");
    getVariable("IOFLAG");
    }
  if (showOptions) {
    printf("Options in effect:\n");
    if (use32Bits) printf("  32-bits\n");
    if (useFp) printf("  Floating point\n");
    if (use1805) printf("  1804/5/6 instructions\n");
    if (useAsm) printf("  Create .asm file\n");
    if (showAsm) printf("  Show assembly listing\n");
    if (outMode == 'B') printf("  Produce binary output\n");
    if (outMode == 'I') printf("  Produce Intel hex output\n");
    if (outMode == 'R') printf("  Produce RCS hex output\n");
    if (showRuntime) printf("  Show runtime modules\n");
    if (showList) printf("  Show source list\n");
    if (createLst) printf("  Create .lst file\n");
    if (showCompiler) printf("  Show compiler output\n");
    if (showSymbols) printf("  Show symbols\n");
    if (showVariables) printf("  Show variables\n");
    if (useElfos) printf("  Produce Elf/OS executable\n");
    printf("\n");
    }
  if (useSelfTerm == 0) {
    addLabel("f_type",lblF_type);
    addLabel("f_setbd",lblF_setbd);
    addLabel("f_inmsg",lblF_inmsg);
    addLabel("f_input",lblF_input);
    addLabel("f_msg",lblF_msg);
    }
  if (getDefine("FILES")) {
    getVariable("IORESULT");
    getVariable("IOFLAG");
    }
  passNumber = 1;
  pass(sourceFile);
  keyBuffer = address;
  variableRAM = (variableStart == 0xffff) ? keyBuffer+iBufferSize : variableStart;
  variableNextAddress = variableRAM;
  passNumber = 2;
  if (getDefine("STRINGS")) {
    getVariable("STMP0_$");
    getVariable("STMP1_$");
    getVariable("STMP2_$");
    getVariable("STMP3_$");
    getVariable("STMP4_$");
    getVariable("STMP5_$");
    getVariable("STMP6_$");
    getVariable("STMP7_$");
    getVariable("STMP8_$");
    getVariable("STMP9_$");
    }
  outCount = 0;
  outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
  if (outFile < 0) {
    printf("Could not open output file: %s\n",outName);
    exit(1);
    }
  if (useAsm) asmFile = open(asmName,O_CREAT|O_TRUNC|O_WRONLY,0666);
  if (createLst) lstFile = fopen(lstName,"w");
  pass(sourceFile);
  if (outCount > 0) writeOutput();
  close(outFile);
  if (useAsm) {
//    for (i=0; i<numberOfVariables; i++) {
//      if (useAsm) {
//        sprintf(buffer,"%s: ",variableNames[i]);
//        while (strlen(buffer) < 10) strcat(buffer," ");
//        strcat(buffer,"dw    0");
//        writeAsm(buffer,"");
//        }
//      }
    close(asmFile);
    }
  if (numNests > 0) printf("#define without #endif\n");
  printf("\n\n");
  printf("Lines compiled: %d\n",lineCount);
  printf("Runtime size  : %d\n",runtime-programStart);
  printf("Program size  : %d\n",codeGenerated-(runtime-programStart));
  printf("Total size    : %d\n",codeGenerated);
  printf("Variable RAM  : %04xh\n",variableRAM);
  printf("Ram           : %04xh-%04xh\n",ramStart,ramEnd);
  printf("Rom           : %04xh-%04xh\n",romStart,romEnd);
  printf("Stack         : %04xh\n",stack);
  printf("Expr. Stack   : %04xh\n",estack);
  if (getDefine("HEAP"))
    printf("Heap          : %04xh\n",heap);
  printf("Program start : %04xh\n",getLabel("start"));
  printf("\n");
  if (showRuntime) {
    printf("Included in runtime:\n");
    if (getDefine("SELFTERM") != 0)   printf("  Delay      %04xh\n",getLabel("delay"));
    if (getDefine("SELFTERM") != 0)   printf("  f_msg      %04xh\n",getLabel("f_msg"));
    if (getDefine("SELFTERM") != 0)   printf("  f_inmsg    %04xh\n",getLabel("f_inmsg"));
    if (getDefine("SELFTERM") != 0)   printf("  f_input    %04xh\n",getLabel("f_input"));
    if (getDefine("SELFTERM") != 0)   printf("  f_read     %04xh\n",getLabel("f_read"));
    if (getDefine("SELFTERM") != 0)   printf("  f_setbd    %04xh\n",getLabel("f_setbd"));
    if (getDefine("SELFTERM") != 0)   printf("  f_type     %04xh\n",getLabel("f_type"));
    if (getDefine("ABS16") != 0)      printf("  abs16      %04xh\n",getLabel("abs16"));
    if (getDefine("ADD16") != 0)      printf("  add16      %04xh\n",getLabel("add16"));
    if (getDefine("HEAP") != 0)       printf("  alloc      %04xh\n",getLabel("alloc"));
    if (getDefine("HEAP") != 0)       printf("  dealloc    %04xh\n",getLabel("dealloc"));
    if (getDefine("HEAP") != 0)       printf("  hfree      %04xh\n",getLabel("hfree"));
    if (getDefine("AND16") != 0)      printf("  and16      %04xh\n",getLabel("and16"));
    if (getDefine("ATOI16") != 0)     printf("  atoi16     %04xh\n",getLabel("atoi"));
    if (getDefine("DIV16") != 0)      printf("  div16      %04xh\n",getLabel("div16"));
    if (getDefine("USEEF") != 0)      printf("  readef     %04xh\n",getLabel("readef"));
    if (getDefine("EQ16") != 0)       printf("  eq16       %04xh\n",getLabel("eq16"));
    if (getDefine("CMP16") != 0)      printf("  false      %04xh\n",getLabel("false"));
    if (getDefine("GT16") != 0)       printf("  gt16       %04xh\n",getLabel("gt16"));
    if (getDefine("GTE16") != 0)      printf("  gte16      %04xh\n",getLabel("gte16"));
    if (getDefine("ITOA16") != 0)     printf("  itoa16     %04xh\n",getLabel("itoa"));
    if (getDefine("ITOA16") != 0)     printf("  tobcd      %04xh\n",getLabel("tobcd"));
    if (getDefine("LT16") != 0)       printf("  lt16       %04xh\n",getLabel("lt16"));
    if (getDefine("LTE16") != 0)      printf("  lte16      %04xh\n",getLabel("lte16"));
    if (getDefine("MOD16") != 0)      printf("  mod16      %04xh\n",getLabel("mod16"));
    if (getDefine("MUL16") != 0)      printf("  mul16      %04xh\n",getLabel("mul16"));
    if (getDefine("NE16") != 0)       printf("  ne16       %04xh\n",getLabel("ne16"));
    if (getDefine("NEXT16") != 0)     printf("  next16     %04xh\n",getLabel("next"));
    if (getDefine("OR16") != 0)       printf("  or16       %04xh\n",getLabel("or16"));
    if (getDefine("RND16") != 0)      printf("  rnd16      %04xh\n",getLabel("rnd16"));
    if (getDefine("SGN16") != 0)      printf("  sgn16      %04xh\n",getLabel("sgn16"));
    if (getDefine("SUB16") != 0)      printf("  sub16      %04xh\n",getLabel("sub16"));
    if (getDefine("CMP16") != 0)      printf("  true       %04xh\n",getLabel("true"));
    if (getDefine("XOR16") != 0)      printf("  xor16      %04xh\n",getLabel("xor16"));
    if (getDefine("LFSR") != 0)       printf("  lfsr       %04xh\n",getLabel("lfsr_lp"));
  
    if (getDefine("ABS32") != 0)      printf("  abs32      %04xh\n",getLabel("abs32"));
    if (getDefine("ADD32") != 0)      printf("  add32      %04xh\n",getLabel("add32"));
    if (getDefine("AND32") != 0)      printf("  and32      %04xh\n",getLabel("and32"));
    if (getDefine("ATOI32") != 0)     printf("  atoi32     %04xh\n",getLabel("atoi32"));
    if (getDefine("CMP32") != 0)      printf("  cmp32      %04xh\n",getLabel("cmp32"));
    if (getDefine("COMP32") != 0)     printf("  comp32     %04xh\n",getLabel("comp32"));
    if (getDefine("DIV32") != 0)      printf("  div32      %04xh\n",getLabel("div32"));
    if (getDefine("EQ32") != 0)       printf("  eq32       %04xh\n",getLabel("eq32"));
    if (getDefine("CMP32") != 0)      printf("  false32    %04xh\n",getLabel("false32"));
    if (getDefine("GT32") != 0)       printf("  gt32       %04xh\n",getLabel("gt32"));
    if (getDefine("GTE32") != 0)      printf("  gte32      %04xh\n",getLabel("gte32"));
    if (getDefine("ICOMP32") != 0)    printf("  icomp32    %04xh\n",getLabel("icomp32"));
    if (getDefine("ITOA32") != 0)     printf("  itoa32     %04xh\n",getLabel("itoa32"));
    if (getDefine("LT32") != 0)       printf("  lt32       %04xh\n",getLabel("lt32"));
    if (getDefine("LTE32") != 0)      printf("  lte32      %04xh\n",getLabel("lte32"));
    if (getDefine("MOD32") != 0)      printf("  mod32      %04xh\n",getLabel("mod32"));
    if (getDefine("MUL32") != 0)      printf("  mul32      %04xh\n",getLabel("mul32"));
    if (getDefine("NE32") != 0)       printf("  ne32       %04xh\n",getLabel("ne32"));
    if (getDefine("NEG32") != 0)      printf("  neg32      %04xh\n",getLabel("neg32"));
    if (getDefine("NEXT32") != 0)     printf("  next32     %04xh\n",getLabel("next32"));
    if (getDefine("NULL32") != 0)     printf("  null32     %04xh\n",getLabel("null32"));
    if (getDefine("OR32") != 0)       printf("  or32       %04xh\n",getLabel("or32"));
    if (getDefine("RND32") != 0)      printf("  rnd32      %04xh\n",getLabel("rnd32"));
    if (getDefine("SGN32") != 0)      printf("  sgn32      %04xh\n",getLabel("sgn32"));
    if (getDefine("SHL32") != 0)      printf("  shl32      %04xh\n",getLabel("shl32"));
    if (getDefine("SHR32") != 0)      printf("  shr32      %04xh\n",getLabel("shr32"));
    if (getDefine("SUB32") != 0)      printf("  sub32      %04xh\n",getLabel("sub32"));
    if (getDefine("ITOA32") != 0)     printf("  tobcd32    %04xh\n",getLabel("tobcd32"));
    if (getDefine("CMP32") != 0)      printf("  true32     %04xh\n",getLabel("true32"));
    if (getDefine("XOR32") != 0)      printf("  xor32      %04xh\n",getLabel("xor32"));
    if (getDefine("ZERO32") != 0)     printf("  zero32     %04xh\n",getLabel("zero32"));
  
    if (getDefine("ABSFP") != 0)      printf("  absfp      %04xh\n",getLabel("absfp"));
    if (getDefine("ADDFP") != 0)      printf("  addfp      %04xh\n",getLabel("addfp"));
    if (getDefine("ATOF") != 0)       printf("  atof       %04xh\n",getLabel("atof"));
    if (getDefine("DIVFP") != 0)      printf("  divfp      %04xh\n",getLabel("divfp"));
    if (getDefine("EQFP") != 0)       printf("  eqfp       %04xh\n",getLabel("eqfp"));
    if (getDefine("FTOA") != 0)       printf("  ftoa       %04xh\n",getLabel("ftoa"));
    if (getDefine("GTFP") != 0)       printf("  gtfp       %04xh\n",getLabel("gtfp"));
    if (getDefine("GTEFP") != 0)      printf("  gtefp      %04xh\n",getLabel("gtefp"));
    if (getDefine("LTFP") != 0)       printf("  ltfp       %04xh\n",getLabel("ltfp"));
    if (getDefine("LTEFP") != 0)      printf("  ltefp      %04xh\n",getLabel("ltefp"));
    if (getDefine("MULFP") != 0)      printf("  mulfp      %04xh\n",getLabel("mulfp"));
    if (getDefine("NEFP") != 0)       printf("  nefp       %04xh\n",getLabel("nefp"));
    if (getDefine("SUBFP") != 0)      printf("  subfp      %04xh\n",getLabel("subfp"));
    if (getDefine("SGNFP") != 0)      printf("  sgnfp      %04xh\n",getLabel("sgnfp"));
    if (getDefine("USEFP") != 0)      printf("  fpargs     %04xh\n",getLabel("fpargs"));
    if (getDefine("USEFP") != 0)      printf("  fpnorm     %04xh\n",getLabel("fpnorm"));
    if (getDefine("USEFP") != 0)      printf("  fpret_0    %04xh\n",getLabel("fpret_0"));
    if (getDefine("USEFP") != 0)      printf("  fpret_a    %04xh\n",getLabel("fpret_a"));
    if (getDefine("USEFP") != 0)      printf("  fpret_b    %04xh\n",getLabel("fpret_b"));
    if (getDefine("USEFP") != 0)      printf("  fpcomp2    %04xh\n",getLabel("fpcomp2"));
    if (getDefine("USEFP") != 0)      printf("  itof       %04xh\n",getLabel("itof"));
    if (getDefine("USEFP") != 0)      printf("  ftoi       %04xh\n",getLabel("ftoi"));
    if (getDefine("USEFP") != 0)      printf("  fpdot1     %04xh\n",getLabel("fpdot1"));
    if (getDefine("USEFP") != 0)      printf("  fpdot5     %04xh\n",getLabel("fpdot5"));
    if (getDefine("USEFP") != 0)      printf("  fp_0       %04xh\n",getLabel("fp_0"));
    if (getDefine("USEFP") != 0)      printf("  fp_1       %04xh\n",getLabel("fp_1"));
    if (getDefine("USEFP") != 0)      printf("  fp_2       %04xh\n",getLabel("fp_2"));
    if (getDefine("USEFP") != 0)      printf("  fp_3       %04xh\n",getLabel("fp_3"));
    if (getDefine("USEFP") != 0)      printf("  fp_10      %04xh\n",getLabel("fp_10"));
    if (getDefine("USEFP") != 0)      printf("  fp_100     %04xh\n",getLabel("fp_100"));
    if (getDefine("USEFP") != 0)      printf("  fp_1000    %04xh\n",getLabel("fp_1000"));
    if (getDefine("USEFP") != 0)      printf("  fp_e       %04xh\n",getLabel("fp_e"));
    if (getDefine("USEFP") != 0)      printf("  fp_pi      %04xh\n",getLabel("fp_pi"));
    if (getDefine("USEFP") != 0)      printf("  fp_halfpi  %04xh\n",getLabel("fp_halfpi"));
  
    if (useTrig != 0) {
      }
    if (getDefine("COSFP") != 0)      printf("  fpcos      %04xh\n",getLabel("fpcos"));
    if (getDefine("EXPFP") != 0)      printf("  fpexp      %04xh\n",getLabel("fpexp"));
    if (getDefine("POWFP") != 0)      printf("  fppow      %04xh\n",getLabel("fppow"));
    if (getDefine("LNFP") != 0)       printf("  fpln       %04xh\n",getLabel("fpln"));
    if (getDefine("SINFP") != 0)      printf("  fpsin      %04xh\n",getLabel("fpsin"));
    if (getDefine("SQRTFP") != 0)     printf("  fpsqrt     %04xh\n",getLabel("fpsqrt"));
    if (getDefine("TANFP") != 0)      printf("  fptan      %04xh\n",getLabel("fptan"));
    if (getDefine("ATANFP") != 0)     printf("  fpatan     %04xh\n",getLabel("fpatan"));
    if (getDefine("ASINFP") != 0)     printf("  fpasin     %04xh\n",getLabel("fpasin"));
    if (getDefine("ACOSFP") != 0)     printf("  fpacos     %04xh\n",getLabel("fpacos"));
  
    if (getDefine("STRCAT") != 0)     printf("  strcat     %04xh\n",getLabel("strcat"));
    if (getDefine("STRCPY") != 0)     printf("  strcpy     %04xh\n",getLabel("strcpy"));
    if (getDefine("STRLEN") != 0)     printf("  strlen     %04xh\n",getLabel("strlen"));
    if (getDefine("STRCMP") != 0)     printf("  strcmp     %04xh\n",getLabel("strcmp"));
    if (getDefine("LEFT") != 0)       printf("  left       %04xh\n",getLabel("left"));
    if (getDefine("MID") != 0)        printf("  mid        %04xh\n",getLabel("mid"));
    if (getDefine("RIGHT") != 0)      printf("  right      %04xh\n",getLabel("right"));
    if (getDefine("LOWER") != 0)      printf("  lower      %04xh\n",getLabel("lower"));
    if (getDefine("UPPER") != 0)      printf("  upper      %04xh\n",getLabel("upper"));
  }

  printf("\n");
  if (showVariables) {
    printf("Variables:\n");
    for (i=0; i<numberOfVariables; i++) {
      sprintf(buffer,"v_%s",variableNames[i]);
      printf("  %-20s  %c %04xh\n",variableNames[i],variableTypes[i],getLabel(buffer));
      }
    printf("\n");
    }
  if (showSymbols) {
    printf("Symbols:\n");
    for (i=0; i<numLabels; i++) {
      printf("  %-20s  %04xh\n",labels[i], labelValues[i]);
      }
    }
  if (createLst) fclose(lstFile);
  }
