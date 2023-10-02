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
  strcpy(currentProc, "_MAIN_");
  source = fopen(filename,"r");
  if (source == NULL) {
    printf("Could not open %s\n",filename);
    exit(1);
    }

  sprintf(buffer,".link .library baslib.lib"); Asm(buffer);
  sprintf(buffer,"f_inmsg:     equ   0%04xh",lblF_inmsg); Asm(buffer);
  sprintf(buffer,"f_type:      equ   0%04xh",lblF_type); Asm(buffer);
  sprintf(buffer,"f_read:      equ   0%04xh",lblF_read); Asm(buffer);
  sprintf(buffer,"f_input:     equ   0%04xh",lblF_input); Asm(buffer);
  sprintf(buffer,"f_msg:       equ   0%04xh",lblF_msg); Asm(buffer);
  sprintf(buffer,"f_setbd:     equ   0%04xh",lblF_setbd); Asm(buffer);

  if (passNumber == 2) {
    for (i=0; i<numExternals; i++)
      if (strcmp(externalProcs[i], "_MAIN_") == 0) {
        sprintf(buffer,"          extrn  %s",externals[i]);
        Asm(buffer);
        }
    }

  address = programStart;
  if (useElfos) address -= 6;
  outAddress = address;
  lastLineNumber = 0;
  lineCount = 0;
  autoLabel = 1;
  autoLine = 1;
  library();
  while (fgets(currentLine, 1023, source) != NULL) {
    lineCount++;
    while (strlen(currentLine) > 0 && currentLine[strlen(currentLine)-1] < 32) currentLine[strlen(currentLine)-1] = 0;
    if (currentLine[0] == '.') strcpy(currentLine,"");
    if (strlen(currentLine) > 0) {
      if (passNumber == 2 && showList) printf("%s\n",currentLine);
      compileLine(currentLine);
      }
    }
  fclose(source);
  if (useStg) {
    Asm("            ldi  STG_.1");
    Asm("            phi  rf");
    Asm("            ldi  STG_.0");
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
  if (useData) {
    if (passNumber == 1) { 
      dataAddress = address;
      }
    strcpy(buffer, "data:     db    ");
    for (i=0; i<numData; i++) {
      sprintf(tmp,"%d",data[i]);
      if (strlen(buffer) > 16) strcat(buffer,",");
      strcat(buffer,tmp);
      if (strlen(buffer) > 60) {
        Asm(buffer);
        strcpy(buffer, "          db    ");
        }
      }
    if (strlen(buffer) > 16) Asm(buffer);
    }
  sprintf(buffer,"iobuffer: ds    %d",iBufferSize); Asm(buffer);
  if (useLfsr) {
    Asm("LFSR_:    dw    0");
    Asm("LFSR__:   dw    0");
    Asm("          public  LFSR_");
    Asm("          public  LFSR__");
    }
  if (useData) {
    Asm("DATA_:    dw    0");
    Asm("          public  DATA_");
    }
  if (useHeap) {
    Asm("HEAP_:    dw    0");
    Asm("          public  HEAP_");
    }
  if (useStg) {
    Asm("STG_:     dw    0");
    }
  if (useFiles) {
    Asm("file1_:   dw    0");
    Asm("file2_:   dw    0");
    Asm("file3_:   dw    0");
    Asm("file4_:   dw    0");
    Asm("file5_:   dw    0");
    Asm("file6_:   dw    0");
    Asm("file7_:   dw    0");
    Asm("file8_:   dw    0");
    }
  Asm("FREE_:    dw    0");
  Asm("          public  FREE_");
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
  if (useElfos) {
    Asm("          end   init");
    }
  return(0);
  }

