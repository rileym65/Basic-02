#include "header.h"

char* con(char* line) {
  int  i;
  word nxt;
  char mode;
  word lineNum;
  word addr;
  word lines[256];
  int  lineCount;
  int  pos;
  line = cexpr(line);
  line = trim(line);
  if (strncasecmp(line,"goto",4) == 0) {
    mode = 'G';
    line += 4;
    }
  if (strncasecmp(line,"gosub",5) == 0) {
    mode = 'S';
    line += 5;
    }
  lineCount = 0;
  while (*line != 0 && *line != ':') {
    line = trim(line);
    if (*line < '0' || *line > '9') {
      showError("Syntax error");
      exit(1);
      }
    line = getNumber(line, &addr);
    lines[lineCount++] = addr;
    line = trim(line);
    if (*line != ':' && *line != ',' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ',') line++;
    }
  Asm("          glo   rc                      ; Get low value of index");
  for (i=0; i<lineCount; i++) {
    Asm("          smi   1                       ; Subtract 1 from index");
    if (findLine(lines[i], &addr) != 0) {
      showError("Line number not found");
      exit(1);
      }
    if (mode == 'G') {
      sprintf(buffer,"          lbz   <%d>                    ; Jump if index is zero", lines[i]); Asm(buffer);
      }
    if (mode == 'S') {
      Asm("          lbnz  $+9                     ; Jump if index not zero");
      Asm("          sep   scall                   ; Perform subroutine call");
      sprintf(buffer,"          dw    <%d>", lines[i]); Asm(buffer);
      addr = 3 + ((lineCount-i-1) * 11);
      sprintf(buffer,"          lbr   $+%d           ; Jump past remaining entries",addr); Asm(buffer);
      }
    }
  return line;
  }

