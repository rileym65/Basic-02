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

