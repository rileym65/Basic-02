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


// dword asm_numStack[256];
// word asm_nstackSize;
// byte asm_tokens[64];
// byte asm_numTokens;
char *sourceLine;
word lstCount;

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
    if (createLst != 0) {
      if (lstCount == 4) {
        fprintf(lstFile,"%s\n",sourceLine);
        fprintf(lstFile,"      ");
        }
      else if (lstCount > 4 && (lstCount % 4) == 0) {
        fprintf(lstFile,"\n");
        fprintf(lstFile,"      ");
        }
      fprintf(lstFile,"%02x ",value);
      lstCount++;
      }
    }
  address++;
  }

void AddExternal(char* proc, char* name) {
  int i;
  for (i=0; i<numExternals; i++)
    if (strcmp(externalProcs[i], proc) == 0 &&
        strcmp(externals[i], name) == 0) return;
  numExternals++;
  if (numExternals == 1) {
    externalProcs = (char**)malloc(sizeof(char*));
    externals = (char**)malloc(sizeof(char*));
    }
  else {
    externalProcs = (char**)realloc(externalProcs,sizeof(char*)*numExternals);
    externals = (char**)realloc(externals,sizeof(char*)*numExternals);
    }
  externalProcs[numExternals-1] = (char*)malloc(strlen(proc) + 1);
  strcpy(externalProcs[numExternals-1], proc);
  externals[numExternals-1] = (char*)malloc(strlen(name) + 1);
  strcpy(externals[numExternals-1], name);
  }

void Asm(char* line) {
  if (passNumber == 2) {
    if (showAsm) printf("%s\n",line);
    write(asmFile, line, strlen(line));
    write(asmFile, lineEnding, strlen(lineEnding));
    }
  }

