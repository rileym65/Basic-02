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

word getVariable(char* name) {
  int i;
  int vsize;
  char vtype;
  vtype = (use32Bits) ? 'L' : 'I';
  if (name[strlen(name)-1] == '!') vtype = 'R';
  if (name[strlen(name)-1] == '$') vtype = 'S';
  if (name[strlen(name)-1] == '#') vtype = 'D';
  if (vtype == 'S') vsize = 2;
  else if (vtype == 'R') vsize = 4;
  else if (vtype == 'D') vsize = 8;
  else if (vtype == 'I') vsize = 2;
  else if (vtype == 'L') vsize = 4;
  for (i=0; i<numberOfVariables; i++) {
    if (strcasecmp(name, variableNames[i]) == 0) return variableAddresses[i];
    }
  numberOfVariables++;
  if (numberOfVariables == 1) {
    variableNames = (char**)malloc(sizeof(char*));
    variableAddresses = (word*)malloc(sizeof(word));
    variableTypes = (char*)malloc(sizeof(char));
    }
  else {
    variableNames = (char**)realloc(variableNames, sizeof(char*) * numberOfVariables);
    variableAddresses = (word*)realloc(variableAddresses, sizeof(word) * numberOfVariables);
    variableTypes = (char*)realloc(variableTypes, sizeof(char) * numberOfVariables);
    }
  variableNames[numberOfVariables-1] = (char*)malloc(strlen(name)+1);
  strcpy(variableNames[numberOfVariables-1], name);
  variableAddresses[numberOfVariables-1] = variableNextAddress;
  variableTypes[numberOfVariables-1] = vtype;
  variableNextAddress += vsize;
  return variableAddresses[numberOfVariables-1];
  }

