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

char* cioff(char* line) {
  word target;
  target = address;
  Asm("          sex   r3                      ; Set X=P");
  Asm("          dis                           ; Turn interrupts off");
  Asm("          db    023h");
  return line;
  }

