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

