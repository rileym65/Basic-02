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

int prepass(char* filename) {
  FILE *source;
  source = fopen(filename,"r");
  if (source == NULL) {
    printf("Could not open %s\n",filename);
    exit(1);
    }
  useStep = 0;
  useData = 0;
  useStep32 = 0;
  useTrig = 0;
  useStrings = 0;

  lblStart = 0;

  while (fgets(currentLine, 1023, source) != NULL) {
    while (strlen(currentLine) > 0 && currentLine[strlen(currentLine)-1] <= 32) currentLine[strlen(currentLine)-1] = 0;
    if (currentLine[0] == '.') {
      if (strcasecmp(currentLine,".fp") == 0) { useFp = -1; use32Bits = -1; }
      if (strcasecmp(currentLine,".32") == 0) { use32Bits = -1; }
      if (strcasecmp(currentLine,".elfos") == 0) { useElfos = -1; programStart = 0x2000; }
      if (strcasecmp(currentLine,".list") == 0) { showList = -1; }
      if (strcasecmp(currentLine,".nolist") == 0) { showList = 0; }
      if (strcasecmp(currentLine,".1805") == 0) { use1805 = -1; }
      if (strcasecmp(currentLine,".vars") == 0) { showVariables = -1; }
      if (strcasecmp(currentLine,".novars") == 0) { showVariables = 0; }
      if (strcasecmp(currentLine,".symbols") == 0) { showSymbols = -1; }
      if (strcasecmp(currentLine,".nosymbols") == 0) { showSymbols = 0; }
      if (strcasecmp(currentLine,".runtime") == 0) { showRuntime = -1; }
      if (strcasecmp(currentLine,".noruntime") == 0) { showRuntime = 0; }
      if (strcasecmp(currentLine,".options") == 0) { showOptions = -1; }
      strcpy(currentLine,"");
      }
    }
  fclose(source);


//  if (SERSEQ == REQ) addDefine("INVQ",1,1);
//  if (SERP == B1) addDefine("SEREF1",1,1);
//  if (SERP == B2) addDefine("SEREF2",1,1);
//  if (SERP == B3) addDefine("SEREF3",1,1);
//  if (SERP == B4) addDefine("SEREF4",1,1);
//  if (SERP == BN1) addDefine("SEREF1I",1,1);
//  if (SERP == BN2) addDefine("SEREF2I",1,1);
//  if (SERP == BN3) addDefine("SEREF3I",1,1);
//  if (SERP == BN4) addDefine("SEREF4I",1,1);

  printf("\n");
  return(0);
  }

