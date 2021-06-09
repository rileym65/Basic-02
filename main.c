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
  printf("Variable RAM  : %04xh\n",variableRAM);
  printf("Ram           : %04xh-%04xh\n",ramStart,ramEnd);
  printf("Rom           : %04xh-%04xh\n",romStart,romEnd);
  printf("Stack         : %04xh\n",stack);
  printf("Expr. Stack   : %04xh\n",estack);
  if (useHeap)
    printf("Heap          : %04xh\n",heap);
  printf("\n");
  printf("Include in runtime:\n");
  if (useAbs != 0) printf("  Abs\n");
  if (useAdd != 0) printf("  Add\n");
  if (useAnd != 0) printf("  And\n");
  if (useAtoI != 0) printf("  AtoI\n");
  if (useCmp != 0) printf("  Cmp\n");
  if (useData != 0) printf("  Data\n");
  if (useDiv != 0) printf("  Div\n");
  if (useEf != 0) printf("  Ef\n");
  if (useEq != 0) printf("  Eq\n");
  if (useGt != 0) printf("  Gt\n");
  if (useGte != 0) printf("  Gte\n");
  if (useHeap != 0) printf("  Heap\n");
  if (useItoA != 0) printf("  ItoA\n");
  if (useLt != 0) printf("  Lt\n");
  if (useLte != 0) printf("  Lte\n");
  if (useMod != 0) printf("  Mod\n");
  if (useMul != 0) printf("  Mul\n");
  if (useNe != 0) printf("  Ne\n");
  if (useNext != 0) printf("  Next\n");
  if (useOr != 0) printf("  Or\n");
  if (useRnd != 0) printf("  Rnd\n");
  if (useSelfTerm != 0) printf("  SelfTerm\n");
  if (useSgn != 0) printf("  Sgn\n");
  if (useStep != 0) printf("  Step\n");
  if (useSub != 0) printf("  Sub\n");
  if (useStg != 0) printf("  Stg\n");
  if (useXor != 0) printf("  Xor\n");
  if (useAbs32 != 0) printf("  Abs32\n");
  if (useAdd32 != 0) printf("  Add32\n");
  if (useAnd32 != 0) printf("  And32\n");
  if (useAtoI32 != 0) printf("  AtoI32\n");
  if (useCmp32 != 0) printf("  Cmp32\n");
  if (useComp32 != 0) printf("  Comp32\n");
  if (useDiv32 != 0) printf("  Div32\n");
  if (useEq32 != 0) printf("  Eq32\n");
  if (useGt32 != 0) printf("  Gt32\n");
  if (useGte32 != 0) printf("  Gte32\n");
  if (useIComp32 != 0) printf("  IComp32\n");
  if (useItoA32 != 0) printf("  ItoA32\n");
  if (useLt32 != 0) printf("  Lt32\n");
  if (useLte32 != 0) printf("  Lte32\n");
  if (useMod32 != 0) printf("  Mod32\n");
  if (useMul32 != 0) printf("  Mul32\n");
  if (useNe32 != 0) printf("  Ne32\n");
  if (useNeg32 != 0) printf("  Neg32\n");
  if (useNext32 != 0) printf("  Next32\n");
  if (useNull32 != 0) printf("  Null32\n");
  if (useOr32 != 0) printf("  Or32\n");
  if (useSgn32 != 0) printf("  Sgn32\n");
  if (useShl32 != 0) printf("  Shl32\n");
  if (useShr32 != 0) printf("  Shr32\n");
  if (useStep32 != 0) printf("  Step32\n");
  if (useSub32 != 0) printf("  Sub32\n");
  if (useXor32 != 0) printf("  Xor32\n");
  if (useZero32 != 0) printf("  Zero32\n");

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

