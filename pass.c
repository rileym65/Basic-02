#include "header.h"

int pass(char* filename) {
  FILE *source;
  source = fopen(filename,"r");
  if (source == NULL) {
    printf("Could not open %s\n",filename);
    exit(1);
    }
  address = programStart;
  if (useElfos) address -= 6;
  outAddress = address;
  lastLineNumber = 0;
  lineCount = 0;
  library();
  while (fgets(currentLine, 1023, source) != NULL) {
    while (strlen(currentLine) > 0 && currentLine[strlen(currentLine)-1] < 32) currentLine[strlen(currentLine)-1] = 0;
    if (strlen(currentLine) > 0) {
      lineCount++;
      if (passNumber == 2 && showList) printf("%s\n",currentLine);
      compileLine(currentLine);
      }
    }
  fclose(source);
  }

