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

char* crepeat(char* line) {
  word addr;
  line = trim(line);
  repeats[numRepeats] = ++autoLabel;
  sprintf(buffer,"lbl_%d:",repeats[numRepeats]); Asm(buffer);
  numRepeats++;
  line = trim(line);
  return line;
  }

