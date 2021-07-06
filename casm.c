#include "header.h"

char* casm(char* line) {
  int  i;
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

