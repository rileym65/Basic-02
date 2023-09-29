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

