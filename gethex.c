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

word getHex(char* line) {
  word number;
  number = 0;
  while ((*line >= '0' && *line <= '9') ||
         (*line >= 'a' && *line <= 'f') ||
         (*line >= 'A' && *line <= 'F')) {
    if (*line >= '0' && *line <= '9') number = (number << 4) + (*line - '0');
    if (*line >= 'a' && *line <= 'f') number = (number << 4) + (*line - 'a') + 10;
    if (*line >= 'A' && *line <= 'F') number = (number << 4) + (*line - 'A') + 10;
    line++;
    }
  return number;
  }

