#include "header.h"

word getVariable(char* name) {
  int i;
  if (passNumber == 1) return 0;
  for (i=0; i<numberOfVariables; i++) {
    if (strcasecmp(name, variableNames[i]) == 0) return variableAddresses[i];
    }
  numberOfVariables++;
  if (numberOfVariables == 1) {
    variableNames = (char**)malloc(sizeof(char*));
    variableAddresses = (word*)malloc(sizeof(word));
    }
  else {
    variableNames = (char**)realloc(variableNames, sizeof(char*) * numberOfVariables);
    variableAddresses = (word*)realloc(variableAddresses, sizeof(word) * numberOfVariables);
    }
  variableNames[numberOfVariables-1] = (char*)malloc(strlen(name)+1);
  strcpy(variableNames[numberOfVariables-1], name);
  variableAddresses[numberOfVariables-1] = variableRAM + (2 * (numberOfVariables - 1));
  return variableAddresses[numberOfVariables-1];
  }

