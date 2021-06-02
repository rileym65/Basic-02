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
  output(GLO+RC);
  if (useAsm) {
    sprintf(buffer,"          glo   rc"); writeAsm(buffer,"Get low value of index");
    }
  for (i=0; i<lineCount; i++) {
    output(SMI); output(0x01);
    if (useAsm) {
      sprintf(buffer,"          smi   1"); writeAsm(buffer,"Subtract 1 from index");
      }
    if (findLine(lines[i], &addr) != 0) {
      showError("Line number not found");
      exit(1);
      }
    if (mode == 'G') {
      output(LBZ); output(addr/256); output(addr%256);
      if (useAsm) {
        sprintf(buffer,"          lbz   l%d",lines[i]); writeAsm(buffer,"Jump if index reached zero");
        }
      }
    if (mode == 'S') {
      nxt = address + 9;
      output(LBNZ); output(nxt/256); output(nxt%256);
      output(SEP+R4); output(addr/256); output(addr%256);
      addr = address + 3 + ((lineCount-i-1) * 11);
      output(LBR); output(addr/256); output(addr%256);
      if (useAsm) {
        sprintf(buffer,"          lbnz  $+9"); writeAsm(buffer,"Jump if index not zero");
        sprintf(buffer,"          sep   scall"); writeAsm(buffer,"Perform subroutine call");
        sprintf(buffer,"          dw    l%d",lines[i]); writeAsm(buffer,"");
        addr = 3 + ((lineCount-i-1) * 11);
        sprintf(buffer,"          lbr   $+%d",addr); writeAsm(buffer,"Jump past remaining entries");
        }
      }
    }
  return line;
  }

