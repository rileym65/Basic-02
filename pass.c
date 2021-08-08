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

int pass(char* filename) {
  int   i;
  char  tmp[16];
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
  if (useStg) {
    Asm("            ldi  [STG_].1");
    Asm("            phi  rf");
    Asm("            ldi  [STG_].0");
    Asm("            plo  rf");
    Asm("            lda  rf");
    Asm("            phi  r2");
    Asm("            ldn  rf");
    Asm("            plo  r2");
    Asm("            sex  r2");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            plo  r6");
    Asm("            ldx");
    Asm("            phi  r6");
    Asm("            sep  sret");
    }
  else if (exitAddress != 0xffff) {
    sprintf(buffer,"          lbr   0%xh                    ; Jump to exit address",exitAddress); Asm(buffer);
    }
  else if (useElfos) {
    Asm("          lbr   0303h                   ; Jump to exit address");
    }
  else {
    Asm("          idl                           ; Idle the CPU");
    Asm("          lbr   $-1");
    }
  if (passNumber == 2 && showCompiler) printf("\n");
  if (useData) {
    if (passNumber == 1) { 
      dataAddress = address;
      }
    if (showCompiler && passNumber == 2) printf("%04x:",address);
    strcpy(buffer, "data:     dw    ");
    for (i=0; i<numData; i++) {
      if (use32Bits) {
        sprintf(tmp,"%d,%d",(data[i] & 0xffff0000) >> 16, data[i] & 0xffff);
        }
      else {
        sprintf(tmp,"%d",data[i]);
        }
      if (strlen(buffer) > 16) strcat(buffer,",");
      strcat(buffer,tmp);
      if (strlen(buffer) > 60) {
        Asm(buffer);
        strcpy(buffer, "          dw    ");
        }
      }
    if (strlen(buffer) > 16) Asm(buffer);
    if (passNumber == 2 && showCompiler) printf("\n");
    }
  sprintf(buffer,"iobuffer: ds    %d",iBufferSize); Asm(buffer);
  if (getDefine("LFSR")) {
    Asm("LFSR_:    dw    0");
    Asm("LFSR__:   dw    0");
    }
  if (useData) {
    Asm("DATA_:    dw    0");
    }
  if (getDefine("HEAP")) {
    Asm("HEAP_:    dw    0");
    }
  Asm("FREE_:    dw    0");
  for (i=0; i<numberOfVariables; i++) {
    sprintf(buffer,"v_%s: ",variableNames[i]);
    while (strlen(buffer) < 10) strcat(buffer," ");
    if (use32Bits)
      strcat(buffer,"dd    0");
    else 
      strcat(buffer,"dw    0");
    Asm(buffer);
    }
    
  Asm("end__:    equ   $");
  return(0);
  }

