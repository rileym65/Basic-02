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

char* ccls(char* line) {
  line = trim(line);
  if (*line != ':' && *line != 0) {
    showError("Syntax error");
    exit(1);
    }
  Asm("          sep   scall                   ; Display message");
  Asm("          dw    f_inmsg");
  Asm("          db    27,'[H',27,'[2J',0");
  return line;
  }

