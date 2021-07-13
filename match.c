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

int match(char* line, char* pattern) {
  int pos;
  line = trim(line);
  pattern = trim(pattern);
  matchCount = 0;
  while (*pattern != 0) {
    pos = 0;
    if (*line == 0 || *line == ':') {
      return 0;
      }
    switch (*pattern) {
      case 'A':
           if ((*line < 'a' || *line > 'z') &&
               (*line < 'A' || *line > 'Z')) return 0;
           while ((*line >= 'a' && *line <= 'z') ||
                  (*line >= 'A' && *line <= 'Z') ||
                  (*line >= '0' && *line <= '9') ||
                   *line == '_') {
             matches[matchCount][pos++] = *line;
             matches[matchCount][pos] = 0;
             line++;
             }
           matchCount++;
           break;
      case '#':
           if (*line == '-') {
             matches[matchCount][pos++] = '-';
             matches[matchCount][pos] = 0;
             line++;
             }
           if (*line < '0' || *line > '9') {
             return 0;
             }
           while (*line >= '0' && *line <= '9') {
             matches[matchCount][pos++] = *line;
             matches[matchCount][pos] = 0;
             line++;
             }
           matchCount++;
           break;
      default :
           if (*line != *pattern) {
             return 0;
             }
           matches[matchCount][pos++] = *line;
           matches[matchCount][pos] = 0;
           matchCount++;
           line++;
           break;
      }
    pattern++;
    line = trim(line);
    pattern=trim(pattern);
    }
  if (*line == 0 || *line == ':') {
    return -1;
    }
  return 0;
  }

