#include "header.h"

int pass(char* filename) {
  int   i;
  word  target;
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
  if (showCompiler && passNumber == 2) printf("%04x:",address);
  if (exitAddress != 0xffff) {
    output(LBR); output(exitAddress / 256); output(exitAddress % 256);
    }
  else if (useElfos) {
    target = 0x303;
    output(LBR); output(target / 256); output(target % 256);
    }
  else {
    target = address;
    output(IDL);
    output(LBR); output(target / 256); output(target % 256);
    }
  if (passNumber == 2 && showCompiler) printf("\n");
  if (useData) {
    if (passNumber == 1) { 
      dataAddress = address;
      }
    if (showCompiler && passNumber == 2) printf("%04x:",address);
    for (i=0; i<numData; i++) {
      output(data[i]/256); output(data[i]%256);
      }
    if (passNumber == 2 && showCompiler) printf("\n");
    }
  }

