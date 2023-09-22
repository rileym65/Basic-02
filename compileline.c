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

int compileLine(char* line) {
  word l;
  listCount = 0;
  char token[256];
  int  pos;
  char *pline;
  if (showCompiler && passNumber == 2) printf("%04x:",address);
  if (passNumber == 2 && createLst)
    fprintf(lstFile,"                  ; %s\n",line);
  if (passNumber == 2 && useAsm) {
    sprintf(buffer,"; %s",line); writeAsm(buffer,"");
    }
  line = trim(line);
  if (*line >= '0' && *line <= '9') {
    line = getNumber(line, &l);
    sprintf(buffer,"l_%d:",l); Asm(buffer);
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
    }
  line = trim(line);
  sprintf(buffer,"la_%d:",autoLabel);
  Asm(buffer);
  while (*line != 0) {
    pos = 0;
    pline = line;
    while (*pline != 0 &&
          ((*pline >= 'a' && *pline <= 'z')  ||
           (*pline >= 'A' && *pline <= 'Z') ||
           (*pline >= '0' && *pline <= '9') ||
           *pline == '_')) token[pos++] = *pline++;
    token[pos] = 0;
    if (strcasecmp(line,"end") == 0) line=cend(line+3);
    else if (strcasecmp(token,"gosub") == 0) line=cgosub(line+5);
    else if (strcasecmp(token,"goto") == 0) line=cgoto(line+4);
    else if (strcasecmp(token,"idle") == 0) line=cidle(line+4);
    else if (strcasecmp(token,"intr") == 0) line=cintr(line+4);
    else if (strcasecmp(token,"ioff") == 0) line=cioff(line+4);
    else if (strcasecmp(token,"ion") == 0) line=cion(line+3);
    else if (strcasecmp(token,"let") == 0) line=clet(line+4);
    else if (strcasecmp(token,"rem") == 0) line=crem(line+3);
    else if (strcasecmp(token,"return") == 0) line=creturn(line+6);
    else if (strcasecmp(token,"poke") == 0) line=cpoke(line+4);
    else if (strcasecmp(token,"dpoke") == 0) line=cdpoke(line+5);
    else if (strcasecmp(token,"on") == 0) line=con(line+2);
    else if (strcasecmp(token,"if") == 0) line=cif(line+2);
    else if (strcasecmp(token,"print") == 0) line=cprint(line+5);
    else if (strcasecmp(token,"input") == 0) line=cinput(line+5);
    else if (strcasecmp(token,"dma") == 0) line=cdma(line+3);
    else if (strcasecmp(token,"q") == 0) line=cq(line+1);
    else if (strcasecmp(token,"out") == 0) line=cout(line+3);
    else if (strcasecmp(token,"for") == 0) line=cfor(line+3);
    else if (strcasecmp(token,"next") == 0) line=cnext(line+4);
    else if (strcasecmp(token,"cls") == 0) line=ccls(line+3);
    else if (strcasecmp(token,"locate") == 0) line=clocate(line+6);
    else if (strcasecmp(token,"data") == 0) line=cdata(line+4);
    else if (strcasecmp(token,"read") == 0) line=cread(line+4);
    else if (strcasecmp(token,"restore") == 0) line=crestore(line+7);
    else if (strcasecmp(token,"asm") == 0) line=casm(line+3);
    else if (strcasecmp(token,"dealloc") == 0) line=cdealloc(line+7);
    else if (useElfos != 0 && strcasecmp(token, "open") == 0) line = copen(line+4);
    else if (useElfos != 0 && strcasecmp(token, "close") == 0) line = cclose(line+5);
    else if (useElfos != 0 && strcasecmp(token, "put") == 0) line = cput(line+3);
    else if (useElfos != 0 && strcasecmp(token, "get") == 0) line = cget(line+3);
    else if (useElfos != 0 && strcasecmp(token, "fwrite") == 0) line = cfwrite(line+6);
    else if (useElfos != 0 && strcasecmp(token, "fread") == 0) line = cfread(line+5);
    else if (useElfos != 0 && strcasecmp(token, "rename") == 0) line = crename(line+6);
    else if (useElfos != 0 && strcasecmp(token, "delete") == 0) line = cdelete(line+6);
    else if (useElfos != 0 && strcasecmp(token, "mkdir") == 0) line = cmkdir(line+5);
    else if (useElfos != 0 && strcasecmp(token, "chdir") == 0) line = cchdir(line+5);
    else if (useElfos != 0 && strcasecmp(token, "rmdir") == 0) line = crmdir(line+5);
    else if (useElfos != 0 && strcasecmp(token, "pos") == 0) line = cpos(line+3);
    else line = clet(line);
  
    line = trim(line);
    if (*line != ':' && *line != 0) {
      showError("Syntax error");
      *line = 0;
      }
    if (*line == ':') {
      line++;
      line = trim(line);
      }
    }
  autoLabel++;
  if (passNumber == 2 && showCompiler) printf("\n");
  return 0;
  }

