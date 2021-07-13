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

char* getNumber(char* line, word* number) {
  *number = 0;
  while (*line >= '0' && *line <= '9') {
    *number = (*number * 10) + (*line - '0');
    line++;
    }
  return line;
  }

