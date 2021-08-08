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

char* cgoto(char* line) {
  word target;
  word lineno;
  line = trim(line);
  line = getNumber(line, &lineno);
  if (lineno == 0) {
    showError("Invalid line number for goto");
    exit(1);
    }
  if (findLine(lineno, &target) != 0) {
    showError("Line number not found");
    exit(1);
    }
  sprintf(buffer,"          lbr   l_%d                    ; Jump",lineno); Asm(buffer);
  return line;
  }

