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

char* cendif(char* line) {
  line = trim(line);
  if (numIfs == 0) {
    showError("ELSE without IF");
    *line = 0;
    return line;
    }
  numIfs--;
  if (ifs[numIfs][0] != 0) {
    sprintf(buffer,"lbl_%d:",ifs[numIfs][0]); Asm(buffer);
    }
  sprintf(buffer,"lbl_%d:",ifs[numIfs][1]); Asm(buffer);
  line = trim(line);
  return line;
  }

