#include "header.h"

int pass(char* filename) {
  int   i;
  word  target;
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
      sprintf(tmp,"%d",data[i]);
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
  if (useAtoI) {
    Asm("keybuf:     db   0");
    }
  }

