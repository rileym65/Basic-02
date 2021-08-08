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

char* casm(char* line) {
  char flag;
  char aline[2048];
  char *pline;
  line = trim(line);
  if (*line != 0) {
    showError("Nothing can follow ASM on a line");
    exit(1);
    }
  flag = -1;
  while (flag) {
    if (fgets(aline, 1023, source) == NULL) flag = 0;
    else {
      while (strlen(aline) > 0 && aline[strlen(aline)-1] <= 32) aline[strlen(aline)-1] = 0;
      pline = aline;
      pline = trim(pline);
      if (strcasecmp(pline,"end") == 0) flag = 0;
        else Asm(aline);
      }
    }
  return line;
  }

