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

//char* asm_convertNumber(char* buffer, dword* value, byte* success) {
//  byte ishex;
//  dword val1,val2;
//  ishex = 0;
//  val1 = 0;
//  val2 = 0;
//  if (*buffer == 'r' || *buffer == 'R') {
//    if (*(buffer+1) == '0') {
//      *value = 0;
//      *success = 0xff;
//      return buffer+2;
//      }
//    if (*(buffer+1) >= '2' && *(buffer+1) <= '9') {
//      *value = *(buffer+1) - '0';
//      *success = 0xff;
//      return buffer+2;
//      }
//    if (*(buffer+1) >= 'a' && *(buffer+1) <= 'f') {
//      *value = *(buffer+1) - 87;
//      *success = 0xff;
//      return buffer+2;
//      }
//    if (*(buffer+1) >= 'A' && *(buffer+1) <= 'F') {
//      *value = *(buffer+1) - 55;
//      *success = 0xff;
//      return buffer+2;
//      }
//    if (*(buffer+1) == '1') {
//      if (*(buffer+2) >= '0' && *(buffer+2) <= '5') {
//        *value = *(buffer+2) - 38;
//        *success = 0xff;
//        return buffer+3;
//        }
//      else {
//        *value = *(buffer+1) - 55;
//        *success = 0xff;
//        return buffer+2;
//        }
//      }
//    }
//  if (*buffer == '\'' && *(buffer+2) == '\'') {
//    buffer++;
//    *value = *buffer;
//    buffer += 2;
//    *success = 0xff;
//    return buffer;
//    }
//  if (*buffer == '%') {
//    buffer++;
//    while (*buffer == '1' || *buffer == '0' || *buffer == '_') {
//      if (*buffer != '_')
//        val1 = (val1 << 1) | (*buffer - '0');
//      buffer++;
//      }
//    *value = val1;
//    *success = 0xff;
//    return buffer;
//    }
//  if (*buffer == '$') {
//    buffer++;
//    if ((*buffer >= '0' && *buffer <= '9') ||
//        (*buffer >= 'a' && *buffer <= 'f') ||
//        (*buffer >= 'A' && *buffer <= 'F'))
//      ishex = 0xff;
//    else {
//      *value = asmAddress;
//      *success = 0xff;
//      return buffer;
//      }
//    }
//  if (ishex == 0 && (*buffer < '0' || *buffer > '9')) {
//    *success = 0;
//    return buffer;
//    }
//  while ((*buffer >= '0' && *buffer <= '9') ||
//         (*buffer >= 'a' && *buffer <= 'f') ||
//         (*buffer >= 'A' && *buffer <= 'F')) {
//      if (*buffer >= '0' && *buffer <= '9') {
//        val1 = (val1 * 10) + (*buffer - '0');
//        val2 = (val2 << 4) | (*buffer - '0');
//        }
//      if (*buffer >= 'a' && *buffer <= 'f')
//        val2 = (val2 << 4) | (*buffer - 87);
//      if (*buffer >= 'A' && *buffer <= 'F')
//        val2 = (val2 << 4) | (*buffer - 55);
//      buffer++;
//    }
//  if (*buffer == 'h' || *buffer == 'H') {
//    ishex = 0xff;
//    buffer++;
//    }
//  *success = 0xff;
//  *value = (ishex != 0) ? val2 : val1;
//  return buffer;
//  }
//
//
//int asm_reduce(char last) {
//  int op;
//  int ret;
//  if (asm_numTokens == 0) return 0;
//  if (asm_tokens[asm_numTokens-1] != OP_NUM) return 0;
//  if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] >= 0x60) {
//    op   = asm_tokens[asm_numTokens-3];
//    asm_numTokens -= 3;
//    ret = 0;
//    if (last) ret = -1;
//    }
//  else if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] == OP_OP) {
//    op   = asm_tokens[asm_numTokens-3];
//    asm_numTokens -= 3;
//    ret = 0;
//    if (asm_numTokens > 0 && asm_tokens[asm_numTokens-1] >= 0x60) ret = -1;
//    if (last) ret = -1;
//    }
//  else if (asm_numTokens > 4 && asm_tokens[asm_numTokens-3] >= 0x10 &&
//                            (asm_tokens[asm_numTokens-4] == OP_NUM ||
//                             asm_tokens[asm_numTokens-4] == OP_NUMFP)) {
//    op   = asm_tokens[asm_numTokens-3];
//    asm_numTokens -= 5;
//    ret = -1;
//    }
//  else {
//    return 0;
//    }
//  switch (op) {
//    case OP_DOT:
//         if (asm_numStack[asm_nstackSize-1] == 0)
//           asm_numStack[asm_nstackSize-2] &= 0x00ff;
//         else
//           asm_numStack[asm_nstackSize-2] >>= 8;
//         asm_nstackSize--;
//         break;
//    case OP_MUL:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] *
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_DIV:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] /
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//    case OP_MOD:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] %
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_ADD:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] +
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_SUB:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] -
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_GT :
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] >
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_LT :
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] <
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_GTE:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] >=
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_LTE:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] <=
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_EQ :
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] ==
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_NE :
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] !=
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_AND:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] &
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_OR :
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] |
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    case OP_XOR:
//         asm_numStack[asm_nstackSize-2] =
//             asm_numStack[asm_nstackSize-2] ^
//             asm_numStack[asm_nstackSize-1];
//         asm_nstackSize--;
//         break;
//    }
//  asm_tokens[asm_numTokens++] = 0;
//  asm_tokens[asm_numTokens++] = OP_NUM;
//  return ret;
//  }
//
//void asm_add(int op) {
//  if (asm_tokens[asm_numTokens-1] >= 0x10) {
//    }
//  while (asm_numTokens > 4 && (op & 0xf0) <= (asm_tokens[asm_numTokens-3] & 0xf0)) {
//    asm_reduce(0);
//    }
//  asm_tokens[asm_numTokens++] = op;
//  }

void addDefine(char* define, int value, int redefine) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      if (redefine) {
        defineValues[i] = value;
        return;
        }
      printf("<ASM>Duplicate define: %s\n",define);
      exit(1);
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (int*)malloc(sizeof(int));
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (int*)realloc(defineValues, sizeof(int) * numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(define) + 1);
  strcpy(defines[numDefines-1], define);
  defineValues[numDefines-1] = value;
  }

int getDefine(char* define) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      return defineValues[i];
      }
  return 0;
  }

void addLabel(char* label, word value) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      printf("<ASM>Duplicate label: %s\n",label);
      exit(1);
      }
  numLabels++;
  if (numLabels == 1) {
    labels = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    }
  else {
    labels = (char**)realloc(labels, sizeof(char*) * numLabels);
    labelValues = (word*)realloc(labelValues, sizeof(word) * numLabels);
    }
  labels[numLabels-1] = (char*)malloc(strlen(label) + 1);
  strcpy(labels[numLabels-1], label);
  labelValues[numLabels-1] = value;
  }

word getLabel(char* label) {
  int i;
  if (passNumber == 1) return 0;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      return labelValues[i];
      }
  printf("<ASM>Label not found: %s\n",label);
  exit(1);
  }

void setLabel(char* label, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      labelValues[i] = value;
      return;
      }
  printf("<ASM>Label not found: %s\n",label);
  exit(1);
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

