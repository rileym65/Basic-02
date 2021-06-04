#include "header.h"

int compileLine(char* line) {
  word l;
  listCount = 0;
  if (showCompiler && passNumber == 2) printf("%04x:",address);
  if (passNumber == 2 && useAsm) {
    sprintf(buffer,"; %s",line); writeAsm(buffer,"");
    }
  line = trim(line);
  if (*line < '0' || *line > '9') {
    showError("Error: Line does not start with a line number");
    return -1;
    }
  line = getNumber(line, &l);
  if (passNumber == 2 && useAsm) {
    sprintf(buffer,"l%d:",l); writeAsm(buffer,"");
    }
  if (l == 0 || l > 65535) {
    showError("Error: Invalid line number");
    return -1;
    }
  if (l < lastLineNumber) {
    showError("Error: Line number out of sequence");
    return -1;
    }
  lastLineNumber = l;
  if (passNumber == 1) {
    lineNumbers[numberOfLines] = l;
    lineAddresses[numberOfLines] = address;
    numberOfLines++;
    }
  line = trim(line);
  while (*line != 0) {
    if (strncasecmp(line,"end",3) == 0) line=cend(line+3);
    else if (strncasecmp(line,"gosub",5) == 0) line=cgosub(line+5);
    else if (strncasecmp(line,"goto",4) == 0) line=cgoto(line+4);
    else if (strncasecmp(line,"idle",4) == 0) line=cidle(line+4);
    else if (strncasecmp(line,"intr",4) == 0) line=cintr(line+4);
    else if (strncasecmp(line,"ioff",4) == 0) line=cioff(line+4);
    else if (strncasecmp(line,"ion",3) == 0) line=cion(line+3);
    else if (strncasecmp(line,"let ",4) == 0) line=clet(line+4);
    else if (strncasecmp(line,"rem",3) == 0) line=crem(line+3);
    else if (strncasecmp(line,"return",6) == 0) line=creturn(line+6);
    else if (strncasecmp(line,"poke",4) == 0) line=cpoke(line+4);
    else if (strncasecmp(line,"dpoke",5) == 0) line=cdpoke(line+5);
    else if (strncasecmp(line,"on",2) == 0) line=con(line+2);
    else if (strncasecmp(line,"if",2) == 0) line=cif(line+2);
    else if (strncasecmp(line,"print",5) == 0) line=cprint(line+5);
    else if (strncasecmp(line,"input",5) == 0) line=cinput(line+5);
    else if (strncasecmp(line,"dma",3) == 0) line=cdma(line+3);
    else if (strncasecmp(line,"q",1) == 0) line=cq(line+1);
    else if (strncasecmp(line,"out",3) == 0) line=cout(line+3);
    else if (strncasecmp(line,"for",3) == 0) line=cfor(line+3);
    else if (strncasecmp(line,"next",4) == 0) line=cnext(line+4);
    else if (strncasecmp(line,"cls",3) == 0) line=ccls(line+3);
    else if (strncasecmp(line,"locate",6) == 0) line=clocate(line+6);
    else if (strncasecmp(line,"data",4) == 0) line=cdata(line+4);
    else if (strncasecmp(line,"read",4) == 0) line=cread(line+4);
    else if (strncasecmp(line,"restore",7) == 0) line=crestore(line+7);
    else if (strncasecmp(line,"asm",3) == 0) line=casm(line+3);
    else if (strncasecmp(line,"dealloc",7) == 0) line=cdealloc(line+7);
    else line = clet(line);
  
    line = trim(line);
    if (*line != ':' && *line != 0) {
      showError("Syntax error");
      exit(1);
      }
    if (*line == ':') {
      line++;
      line = trim(line);
      }
    }
  if (passNumber == 2 && showCompiler) printf("\n");
  return 0;
  }

