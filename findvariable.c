#include "header.h"

int findVariable(char* name) {
  int i;
  int vsize;
  if (passNumber == 1) return 0;
  vsize = (use32Bits) ? 4 : 2;
  for (i=0; i<numberOfVariables; i++) {
    if (strcasecmp(name, variableNames[i]) == 0) return i;
    }
  return -1;
  }

