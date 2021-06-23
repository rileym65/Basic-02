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
  showVariables = 0;
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
  lblMdNorm = 0x0000;
  lblStart = 0x0000;
  lblScall = 0x0000;
  lblSret  = 0x0000;
  numberOfLines = 0;
  numberOfVariables = 0;
  numData = 0;
  numDataLines = 0;
  numLabels = 0;
  codeGenerated = 0;
  highest = 0;
  prepass(sourceFile);
  addLabel("f_type",lblF_type);
  addLabel("f_setbd",lblF_setbd);
  addLabel("f_inmsg",lblF_inmsg);
  addLabel("f_input",lblF_input);
  addLabel("f_msg",lblF_msg);
  passNumber = 1;
  pass(sourceFile);
  keyBuffer = address;
  variableRAM = (variableStart == 0xffff) ? keyBuffer+iBufferSize : variableStart;
  passNumber = 2;
  if (useRnd) {
    getVariable("LFSR_");
    getVariable("LFSR__");
    }
  if (useData) {
    getVariable("DATA_");
    }
  if (useHeap) {
    getVariable("HEAP_");
    }
  getVariable("FREE_");
  outCount = 0;
  outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
  if (outFile < 0) {
    printf("Could not open output file: %s\n",outName);
    exit(1);
    }
  if (useAsm) asmFile = open(asmName,O_CREAT|O_TRUNC|O_WRONLY,0666);
  pass(sourceFile);
  if (outCount > 0) writeOutput();
  close(outFile);
  if (useAsm) {
    for (i=0; i<numberOfVariables; i++) {
      if (useAsm) {
        sprintf(buffer,"%s: ",variableNames[i]);
        while (strlen(buffer) < 10) strcat(buffer," ");
        strcat(buffer,"dw    0");
        writeAsm(buffer,"");
        }
      }
    close(asmFile);
    }
  printf("\n");
  printf("Lines compiled: %d\n",lineCount);
  printf("Runtime size  : %d\n",runtime-programStart);
  printf("Program size  : %d\n",codeGenerated-(runtime-programStart));
  printf("Total size    : %d\n",codeGenerated);
  printf("Variable RAM  : %04xh\n",variableRAM);
  printf("Ram           : %04xh-%04xh\n",ramStart,ramEnd);
  printf("Rom           : %04xh-%04xh\n",romStart,romEnd);
  printf("Stack         : %04xh\n",stack);
  printf("Expr. Stack   : %04xh\n",estack);
  if (useHeap)
    printf("Heap          : %04xh\n",heap);
  printf("\n");
  printf("Included in runtime:\n");
  if (useAbs != 0)      printf("  Abs        %04x\n",getLabel("abs16"));
  if (useAdd != 0)      printf("  Add        %04x\n",getLabel("add16"));
  if (useHeap != 0)     printf("  Alloc      %04x\n",getLabel("alloc"));
  if (useAnd != 0)      printf("  And        %04x\n",getLabel("and16"));
  if (useAtoI != 0)     printf("  AtoI       %04x\n",getLabel("atoi"));
  if (useHeap != 0)     printf("  Dealloc    %04x\n",getLabel("dealloc"));
  if (useSelfTerm != 0) printf("  Delay      %04x\n",getLabel("delay"));
  if (useDiv != 0)      printf("  Div        %04x\n",getLabel("div16"));
  if (useEf != 0)       printf("  ReadEf     %04x\n",getLabel("readef"));
  if (useEq != 0)       printf("  Eq         %04x\n",getLabel("eq16"));
  if (useCmp != 0)      printf("  False      %04x\n",getLabel("false"));
  if (useSelfTerm != 0) printf("  f_msg      %04x\n",getLabel("f_msg"));
  if (useSelfTerm != 0) printf("  f_inmsg    %04x\n",getLabel("f_inmsg"));
  if (useSelfTerm != 0) printf("  f_input    %04x\n",getLabel("f_input"));
  if (useSelfTerm != 0) printf("  f_read     %04x\n",getLabel("f_read"));
  if (useSelfTerm != 0) printf("  f_setbd    %04x\n",getLabel("f_setbd"));
  if (useSelfTerm != 0) printf("  f_type     %04x\n",getLabel("f_type"));
  if (useGt != 0)       printf("  Gt         %04x\n",getLabel("gt16"));
  if (useGte != 0)      printf("  Gte        %04x\n",getLabel("gte16"));
  if (useHeap != 0)     printf("  Hfree      %04x\n",getLabel("hfree"));
  if (useItoA != 0)     printf("  ItoA       %04x\n",getLabel("itoa"));
  if (useLt != 0)       printf("  Lt         %04x\n",getLabel("lt16"));
  if (useLte != 0)      printf("  Lte        %04x\n",getLabel("lte16"));
  if (useMod != 0)      printf("  Mod        %04x\n",getLabel("mod16"));
  if (useMul != 0)      printf("  Mul        %04x\n",getLabel("mul16"));
  if (useNe != 0)       printf("  Ne         %04x\n",getLabel("ne16"));
  if (useNext != 0)     printf("  Next       %04x\n",getLabel("next"));
  if (useOr != 0)       printf("  Or         %04x\n",getLabel("or16"));
  if (useRnd != 0)      printf("  Rnd        %04x\n",getLabel("rnd16"));
  if (useSgn != 0)      printf("  Sgn        %04x\n",getLabel("sgn16"));
  if (useSub != 0)      printf("  Sub        %04x\n",getLabel("sub16"));
  if (useCmp != 0)      printf("  True       %04x\n",getLabel("true"));
  if (useXor != 0)      printf("  Xor        %04x\n",getLabel("xor16"));
  if (useAbs32 != 0)    printf("  Abs32      %04x\n",getLabel("abs32"));
  if (useAdd32 != 0)    printf("  Add32      %04x\n",getLabel("add32"));
  if (useAnd32 != 0)    printf("  And32      %04x\n",getLabel("abs32"));
  if (useAtoI32 != 0)   printf("  AtoI32     %04x\n",getLabel("atoi32"));
  if (useCmp32 != 0)    printf("  Cmp32      %04x\n",getLabel("cmp32"));
  if (useComp32 != 0)   printf("  Comp32     %04x\n",getLabel("comp32"));
  if (useDiv32 != 0)    printf("  Div32      %04x\n",getLabel("div32"));
  if (useEq32 != 0)     printf("  Eq32       %04x\n",getLabel("eq32"));
  if (useGt32 != 0)     printf("  Gt32       %04x\n",getLabel("gt32"));
  if (useGte32 != 0)    printf("  Gte32      %04x\n",getLabel("gte32"));
  if (useIComp32 != 0)  printf("  IComp32    %04x\n",getLabel("icomp32"));
  if (useItoA32 != 0)   printf("  ItoA32     %04x\n",getLabel("itoa32"));
  if (useLt32 != 0)     printf("  Lt32       %04x\n",getLabel("lt32"));
  if (useLte32 != 0)    printf("  Lte32      %04x\n",getLabel("lte32"));
  if (useMod32 != 0)    printf("  Mod32      %04x\n",getLabel("mod32"));
  if (useMul32 != 0)    printf("  Mul32      %04x\n",getLabel("mul32"));
  if (useNe32 != 0)     printf("  Ne32       %04x\n",getLabel("ne32"));
  if (useNeg32 != 0)    printf("  Neg32      %04x\n",getLabel("neg32"));
  if (useNext32 != 0)   printf("  Next32     %04x\n",getLabel("next32"));
  if (useNull32 != 0)   printf("  Null32     %04x\n",getLabel("null2"));
  if (useOr32 != 0)     printf("  Or32       %04x\n",getLabel("or32"));
  if (useSgn32 != 0)    printf("  Sgn32      %04x\n",getLabel("sgn32"));
  if (useShl32 != 0)    printf("  Shl32      %04x\n",getLabel("shl32"));
  if (useShr32 != 0)    printf("  Shr32      %04x\n",getLabel("shr32"));
  if (useStep32 != 0)   printf("  Step32     %04x\n",getLabel("step32"));
  if (useSub32 != 0)    printf("  Sub32      %04x\n",getLabel("sub32"));
  if (useXor32 != 0)    printf("  Xor32      %04x\n",getLabel("xor32"));
  if (useZero32 != 0)   printf("  Zero32     %04x\n",getLabel("zero32"));
  if (useAbsFp != 0)    printf("  AbsFp      %04x\n",getLabel("absfp"));
  if (useAddFp != 0)    printf("  AddFp      %04x\n",getLabel("addfp"));
  if (useAtoF != 0)     printf("  AtoF       %04x\n",getLabel("atof"));
  if (useDivFp != 0)    printf("  DivFp      %04x\n",getLabel("divfp"));
  if (useEqFp != 0)     printf("  EqFp       %04x\n",getLabel("eqfp"));
  if (useFtoA != 0)     printf("  FtoA       %04x\n",getLabel("ftoa"));
  if (useGtFp != 0)     printf("  GtFP       %04x\n",getLabel("gtfp"));
  if (useGteFp != 0)    printf("  GteFP      %04x\n",getLabel("gtefp"));
  if (useLtFp != 0)     printf("  LtFP       %04x\n",getLabel("ltfp"));
  if (useLteFp != 0)    printf("  LteFP      %04x\n",getLabel("ltefp"));
  if (useMulFp != 0)    printf("  MulFp      %04x\n",getLabel("mulfp"));
  if (useNeFp != 0)     printf("  NeFp       %04x\n",getLabel("nefp"));
  if (useSubFp != 0)    printf("  SubFp      %04x\n",getLabel("subfp"));
  if (useSgnFp != 0)    printf("  SgnFp      %04x\n",getLabel("sgnfp"));
  if (useFp != 0) {
                        printf("  fpargs     %04x\n",getLabel("fpargs"));
                        printf("  fpnorm     %04x\n",getLabel("fpnorm"));
                        printf("  fpret_0    %04x\n",getLabel("fpret_0"));
                        printf("  fpret_a    %04x\n",getLabel("fpret_a"));
                        printf("  fpret_b    %04x\n",getLabel("fpret_b"));
                        printf("  fpcomp2    %04x\n",getLabel("fpcomp2"));
                        printf("  itof       %04x\n",getLabel("itof"));
                        printf("  ftoi       %04x\n",getLabel("ftoi"));
    }
  if (useTrig != 0) {
    }
  if (useCos != 0)      printf("  FpCos      %04x\n",getLabel("fpcos"));
  if (useExp != 0)      printf("  FpExp      %04x\n",getLabel("fpexp"));
  if (useLn  != 0)      printf("  FpLn       %04x\n",getLabel("fpln"));
  if (useSin != 0)      printf("  FpSin      %04x\n",getLabel("fpsin"));
  if (useTan != 0)      printf("  FpTan      %04x\n",getLabel("fptan"));

  printf("\n");
  if (showVariables) {
    printf("Variables:\n");
    for (i=0; i<numberOfVariables; i++) {
      printf("  %-20s  %04x\n",variableNames[i],variableAddresses[i]);
      }
    printf("\n");
    }
  if (showSymbols) {
    printf("Symbols:\n");
    for (i=0; i<numLabels; i++) {
      printf("  %-20s  %04x\n",labels[i], labelValues[i]);
      }
    }
  }

