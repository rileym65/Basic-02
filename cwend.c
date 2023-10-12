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

char* cwend(char* line) {
  line = trim(line);
  if (numWhiles == 0) {
    showError("WEND without WHILE");
    *line = 0;
    return line;
    }
  numWhiles--;
  sprintf(buffer,"          lbr   lbl_%d                  ; Jump if test failed",whiles[numWhiles][0]); Asm(buffer);
  sprintf(buffer,"lbl_%d:",whiles[numWhiles][1]); Asm(buffer);
  line = trim(line);
  return line;
  }

