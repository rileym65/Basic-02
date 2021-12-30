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

char* copen(char* line) {
  char mode;
  byte fnum;
  line = trim(line);
  if (*line != '"') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line++;
  Asm("          ldi   iobuffer.1              ; Point to i/o buffer");
  Asm("          phi   rf");
  Asm("          ldi   iobuffer.0");
  Asm("          plo   rf");
  while (*line != 0 && *line != '"') {
    sprintf(buffer,"          ldi   0%02xh                    ; get next character",*line++);
    Asm(buffer);
    Asm("          str   rf                      ; write to i/o buffer");
    Asm("          inc   rf                      ; point to next position");
    }
  Asm("          ldi   0                       ; need terminator");
  Asm("          str   rf                      ; write to i/o buffer");
  if (*line != '"') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line++;
  line = trim(line);
  if (strncasecmp(line, "for", 3) != 0) {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line += 4;
  line = trim(line);
  if (strncasecmp(line, "input", 5) == 0) { mode = 'I'; line += 5; }
  else if (strncasecmp(line, "output", 6) == 0) { mode = 'O'; line += 6; }
  else if (strncasecmp(line, "append", 6) == 0) { mode = 'A'; line += 6; }
  else {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line = trim(line);
  if (strncasecmp(line, "as", 2) != 0) {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line += 2;
  line = trim(line);
  if (*line != '#') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  line++;
  if (*line < '1' || *line > '8') {
    showError("Syntax error");
    *line = 0;
    return line;
    }
  fnum = *line - '1';
  line++;
  line = trim(line);
  Asm("          ldi   013h                    ; Need to allocate 531 bytes");
  Asm("          plo   rc");
  Asm("          ldi   2");
  Asm("          phi   rc");
  Asm("          sep   scall                   ; Allocate memory from the heap");
  Asm("          dw    alloc");

  sprintf(buffer,"          ldi   (file1_+%d*2).0         ; Point to file handle",fnum % 256);
  Asm(buffer);
  Asm("          plo   rd");
  sprintf(buffer,"          ldi   (file1_+%d*2).1",fnum / 256);
  Asm(buffer);
  Asm("          phi   rd");
  Asm("          ghi   rf                      ; store allocated memory to handle");
  Asm("          str   rd");
  Asm("          inc   rd");
  Asm("          glo   rf");
  Asm("          str   rd");
  Asm("          ghi   rf                      ; transfer fildes address to RD");
  Asm("          phi   rd");
  Asm("          glo   rf");
  Asm("          plo   rd");
  Asm("          glo   rf                      ; DTA is 19 bytes highter");
  Asm("          adi   19");
  Asm("          plo   rf");
  Asm("          ghi   rf                      ; propagate carry");
  Asm("          adci  0");
  Asm("          phi   rf                      ; RF now points to dta");
  Asm("          inc   rd                      ; point to DTA entry in FILDES");
  Asm("          inc   rd");
  Asm("          inc   rd");
  Asm("          inc   rd");
  Asm("          ghi   rf                      ; write DTA address");
  Asm("          str   rd");
  Asm("          inc   rd");
  Asm("          glo   rf");
  Asm("          str   rd");
  Asm("          dec   rd                      ; restore RD");
  Asm("          dec   rd");
  Asm("          dec   rd");
  Asm("          dec   rd");
  Asm("          dec   rd");
  Asm("          ldi   iobuffer.1              ; Point to filename");
  Asm("          phi   rf");
  Asm("          ldi   iobuffer.0");
  Asm("          plo   rf");
  switch (mode) {
    case 'I':
         Asm("          ldi   16                      ; Open for read only");
         break;
    case 'O':
         Asm("          ldi   3                       ; Open for writing");
         break;
    case 'A':
         Asm("          ldi   5                       ; Open for append");
         break;
    }
  Asm("          plo   r7                      ; set open flags");
  Asm("          sep   scall                   ; Call Elf/OS to open the file");
  Asm("          dw    0306h");
  Asm("          sep   scall                   ; Set I/O return variables");
  Asm("          dw    ioresults");




  while (*line != 0 && *line != ':') line++;
  return line;
  }

