#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

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

void processRAM(char* buffer) {
  ramStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -ram\n");
    exit(1);
    }
  buffer++;
  ramEnd = getHex(buffer);
  }

void processROM(char* buffer) {
  romStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -rom\n");
    exit(1);
    }
  buffer++;
  romEnd = getHex(buffer);
  }

int main(int argc, char** argv) {
  int i;
  char sourceFile[1024];
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
  ramStart = 0x0000;
  ramEnd = 0xffff;
  romStart = 0xffff;
  romEnd = 0xffff;
  showCompiler = 0;
  showList = 0;
  showVariables = 0;
  stack = 0;
  estack = 0;
  useSelfTerm = 0;
  lblF_inmsg = 0xff66;
  lblF_type = 0xff03;
  lblF_read = 0xff06;
  lblF_input = 0xff0f;
  lblF_msg = 0xff09;
  lblF_setbd = 0xff2d;
  strcpy(lineEnding,"\n");
  SERSEQ = SEQ;
  SERREQ = REQ;
  i = 1;
  while (i < argc) {
    if (strcmp(argv[i],"-b") == 0) outMode = 'B';
    if (strcmp(argv[i],"-i") == 0) outMode = 'I';
    if (strcmp(argv[i],"-r") == 0) outMode = 'R';
    if (strcmp(argv[i],"-l") == 0) showList = -1;
    if (strcmp(argv[i],"-c") == 0) showCompiler = -1;
    if (strcmp(argv[i],"-v") == 0) showVariables = -1;
    if (strcmp(argv[i],"-lf") == 0) strcpy(lineEnding,"\n");
    if (strcmp(argv[i],"-cr") == 0) strcpy(lineEnding,"\r");
    if (strcmp(argv[i],"-crlf") == 0) strcpy(lineEnding,"\r\n");
    if (strcmp(argv[i],"-lfcr") == 0) strcpy(lineEnding,"\n\r");
    if (strcmp(argv[i],"-term=bios") == 0) {
      useSelfTerm = 0;
      lblF_inmsg = 0xff66;
      lblF_type = 0xff03;
      lblF_read = 0xff06;
      lblF_input = 0xff0f;
      lblF_msg = 0xff09;
      lblF_setbd = 0xff2d;
      }
    if (strcmp(argv[i],"-term=self") == 0) {
      useSelfTerm = 0xff;
      lblF_inmsg = 0x0000;
      lblF_type = 0x0000;
      lblF_read = 0x0000;
      lblF_input = 0x0000;
      lblF_msg = 0x0000;
      lblF_setbd = 0x0000;
      }
    if (strcmp(argv[i],"-term=none") == 0) {
      useSelfTerm = 0;
      lblF_inmsg = 0xffff;
      lblF_type = 0xffff;
      lblF_read = 0xffff;
      lblF_input = 0xffff;
      lblF_msg = 0xffff;
      lblF_setbd = 0xffff;
      }
    if (strncmp(argv[i],"-start=",7) == 0) programStart=getHex(argv[i]+7);
    if (strncmp(argv[i],"-vars=",6) == 0) variableStart=getHex(argv[i]+6);
    if (strncmp(argv[i],"-ram=",5) == 0) processRAM(argv[i]+5);
    if (strncmp(argv[i],"-rom=",5) == 0) processROM(argv[i]+5);
    if (strncmp(argv[i],"-stack=",7) == 0) stack=getHex(argv[i]+7);
    if (strncmp(argv[i],"-estack=",8) == 0) estack=getHex(argv[i]+8);
    if (strncmp(argv[i],"-keybuf=",8) == 0) iBufferSize=getHex(argv[i]+8);
    else strcpy(sourceFile,argv[i]);
    i++;
    }
  if (strlen(sourceFile) == 0) {
    printf("No source file specified\n");
    exit(1);
    }
  strcpy(outName, sourceFile);
  if (strstr(outName,".bas") != NULL) {
    *(strstr(outName,".bas")) = 0;
    }
  switch (outMode) {
    case 'R': strcat(outName, ".prg"); break;
    case 'I': strcat(outName, ".hex"); break;
    case 'B': strcat(outName, ".bin"); break;
    }
  printf("out: %s\n",outName);
  if (programStart == 0xffff) programStart = 0x0000;
  if (programStart >= ramStart && programStart <= ramEnd) compMode = 'A';
  if (programStart >= romStart && programStart <= romEnd) compMode = 'O';
  if (stack == 0) stack = ramEnd;
  if (estack == 0) estack = stack - 256;
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
  codeGenerated = 0;
  prepass(sourceFile);
  passNumber = 1;
  pass(sourceFile);
  variableRAM = (variableStart == 0xffff) ? address : variableStart;
  passNumber = 2;
  outCount = 0;
  outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY,0666);
  if (outFile < 0) {
    printf("Could not open output file: %s\n",outName);
    exit(1);
    }
  pass(sourceFile);
  if (outCount > 0) writeOutput();
  close(outFile);
  printf("\n");
  printf("Lines compiled: %d\n",lineCount);
  printf("Code generated: %d\n",codeGenerated);
  printf("Variable RAM  : %04x\n",variableRAM);
  printf("Ram           : %04x-%04x\n",ramStart,ramEnd);
  printf("Rom           : %04x-%04x\n",romStart,romEnd);
  printf("Stack         : %04x\n",stack);
  printf("Expr. Stack   : %04x\n",estack);
  printf("\n");
  printf("Include in runtime:\n");
  if (lblScall != 0)  printf("  Scall         : %04x\n",lblScall);
  if (lblSret != 0)  printf("  Sret          : %04x\n",lblSret);
  if (lblAdd != 0)  printf("  Add16         : %04x\n",lblAdd);
  if (lblSub != 0)  printf("  Sub16         : %04x\n",lblSub);
  if (lblMul != 0)  printf("  Mul16         : %04x\n",lblMul);
  if (lblDiv != 0)  printf("  Div16         : %04x\n",lblDiv);
  if (lblAnd != 0)  printf("  And16         : %04x\n",lblAnd);
  if (lblOr != 0)  printf("  Or16          : %04x\n",lblOr);
  if (lblXor != 0)  printf("  Xor16         : %04x\n",lblXor);
  if (lblTrue != 0)  printf("  Cmp16         : %04x\n",lblTrue);
  if (lblEq != 0)  printf("  Eq16          : %04x\n",lblEq);
  if (lblNe != 0)  printf("  Ne16          : %04x\n",lblNe);
  if (lblGt != 0)  printf("  Gt16          : %04x\n",lblGt);
  if (lblLt != 0)  printf("  Lt16          : %04x\n",lblLt);
  if (lblGte != 0)  printf("  Gte16         : %04x\n",lblGte);
  if (lblLte != 0)  printf("  Lte16         : %04x\n",lblLte);
  if (lblItoA != 0)  printf("  ItoA          : %04x\n",lblItoA);
  if (lblAtoI != 0)  printf("  AtoI          : %04x\n",lblAtoI);
  if (lblF_inmsg != 0)  printf("  f_inmsg       : %04x\n",lblF_inmsg);
  if (lblF_msg != 0)  printf("  f_msg         : %04x\n",lblF_msg);
  if (lblF_type != 0)  printf("  f_type        : %04x\n",lblF_type);
  if (lblF_read != 0)  printf("  f_read        : %04x\n",lblF_read);
  if (lblF_input != 0)  printf("  f_input       : %04x\n",lblF_input);
  if (lblF_setbd != 0)  printf("  f_setbd       : %04x\n",lblF_setbd);
  printf("\n");

  if (showVariables) {
    printf("Variables:\n");
    for (i=0; i<numberOfVariables; i++) {
      printf("%-20s  %04x\n",variableNames[i],variableAddresses[i]);
      }
    }
  }

