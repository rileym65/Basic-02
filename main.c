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
  printf("BASIC/02 Compiler v%s\n",VERSION);
  printf("by Michael H. Riley\n");
  printf("\n");
  strcpy(sourceFile,"");
  if (argc < 2) {
    printf("Usage: sbc [options] filename\n");
    exit(1);
    }
  errorCount = 0;
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
  useLfsr = 0;
  useStg = 0;
  useAsm = 0;
  use1805 = 0;
  use32Bits = 0;
  useFp = 0;
  useHeap = 0;
  useFiles = 0;
  useTerminal = 0;
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
//  if (useSelfTerm == 0) {
//    addLabel("f_type",lblF_type);
//    addLabel("f_setbd",lblF_setbd);
//    addLabel("f_inmsg",lblF_inmsg);
//    addLabel("f_input",lblF_input);
//    addLabel("f_msg",lblF_msg);
//    }
  if (useFiles) {
    getVariable("IORESULT");
    getVariable("IOFLAG");
    }
  passNumber = 1;
  pass(sourceFile);
  if (errorCount != 0) {
    printf("Errors: %d\n",errorCount);
    printf("Compilation aborted\n");
    exit(1);
    }
  keyBuffer = address;
  variableRAM = (variableStart == 0xffff) ? keyBuffer+iBufferSize : variableStart;
  variableNextAddress = variableRAM;
  passNumber = 2;
  if (useStrings) {
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
  printf("Error count   : %d\n",errorCount);
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
//  printf("Program start : %04xh\n",getLabel("start"));
  printf("\n");
  if (showRuntime) {
    printf("Included in runtime:\n");
    for (i=0; i<numExternals; i++)
      printf("  %s:%s\n", externalProcs[i], externals[i]);
  }

  printf("\n");
  if (showVariables) {
    printf("Variables:\n");
    for (i=0; i<numberOfVariables; i++) {
      sprintf(buffer,"v_%s",variableNames[i]);
      printf("  %-20s  %c\n",variableNames[i],variableTypes[i]);
      }
    printf("\n");
    }
  if (createLst) fclose(lstFile);
  }

