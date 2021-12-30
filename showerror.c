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

void showError(char* msg) {
  printf("\n*** %s\n", msg);
  printf("%d:%s\n",lineCount, currentLine);
  errorCount++;
  }


