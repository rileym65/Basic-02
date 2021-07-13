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

int findLine(word lineNumber, word* address) {
  int i;
  if (passNumber == 1) {
    *address = 0;
    return 0;
    }
  for (i=0; i<numberOfLines; i++)
    if (lineNumbers[i] == lineNumber) {
      *address = lineAddresses[i];
      return 0;
      }
  return -1;
  }

int findNextLine(word lineNumber, word* address) {
  int i;
  if (passNumber == 1) {
    *address = 0;
    return 0;
    }
  for (i=0; i<numberOfLines; i++)
    if (lineNumbers[i] == lineNumber) {
      *address = lineAddresses[i+1];
      return 0;
      }
  return -1;
  }

int findNextLineNumber(word lineNumber, word* address) {
  int i;
  if (passNumber == 1) {
    *address = 0;
    return 0;
    }
  for (i=0; i<numberOfLines; i++)
    if (lineNumbers[i] == lineNumber) {
      *address = lineNumbers[i+1];
      return 0;
      }
  return -1;
  }

