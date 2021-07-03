#include "header.h"

char* cprint(char* line) {
  char qt;
  char last;
  line = trim(line);
  if (lblF_inmsg == 0xffff) {
    qt = 0;
    while (*line != 0 && ((qt == 1) || (qt == 0 && *line != ':'))) {
      if (*line == '"') qt = 1-qt;
      line++;
      }
    return line;
    }
  last = ' ';
  while (*line != ':' && *line != 0) {
    line=trim(line);
    if (*line == '"') {
      Asm("          sep   scall                   ; Display message");
      Asm("          dw    f_inmsg");
      strcpy(buffer,"          db    '");
      line++;
      while (*line != '"' && *line != 0) {
        if (*line == '\'') {
          strcat(buffer,"',39,'");
          line++;
          }
        else {
          buffer[strlen(buffer)+1] = 0;
          buffer[strlen(buffer)] = *line++;
          }
        }
      strcat(buffer,"',0"); Asm(buffer);
      if (*line == '"') line++;
      last = ' ';
      }
    else if (*line == ',') {
      Asm("          ldi   9                       ; Display a tab character");
      Asm("          sep   scall                   ; Display cr/lf");
      Asm("          dw    f_type");
      line++;
      last = ',';
      }
    else if (*line == ';') {
      line++;
      last = ';';
      }
    else {
      line = cexpr(line, 2);
      if (useFp) {
        if (tokens[1] == OP_NUM) {
          Asm("          inc   r7                      ; Point to expression result");
          Asm("          glo   r7");
          Asm("          plo   rf");
          Asm("          ghi   r7");
          Asm("          phi   rf");
          Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
          Asm("          phi   rd");
          Asm("          ldi   [iobuffer].0");
          Asm("          plo   rd");
          Asm("          sep   scall                   ; Display integer value");
          Asm("          dw    itoa32");
          Asm("          ldi   [iobuffer].1            ; Display result");
          Asm("          phi   rf");
          Asm("          ldi   [iobuffer].0");
          Asm("          plo   rf");
          Asm("          sep   scall");
          Asm("          dw    f_msg");
          Asm("          inc   r7                      ; Remove expression result");
          Asm("          inc   r7");
          Asm("          inc   r7");
          }
        else if (tokens[1] == OP_NUMFP) {
          Asm("          inc   r7                      ; Point to expression result");
          Asm("          glo   r7");
          Asm("          plo   rf");
          Asm("          ghi   r7");
          Asm("          phi   rf");
          Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
          Asm("          phi   rd");
          Asm("          ldi   [iobuffer].0");
          Asm("          plo   rd");
          Asm("          sep   scall                   ; Display floating point value");
          Asm("          dw    ftoa");
          Asm("          ldi   [iobuffer].1            ; Display result");
          Asm("          phi   rf");
          Asm("          ldi   [iobuffer].0");
          Asm("          plo   rf");
          Asm("          sep   scall");
          Asm("          dw    f_msg");
          Asm("          inc   r7                      ; Remove expression result");
          Asm("          inc   r7");
          Asm("          inc   r7");
          }
        else {
printf("Expression error\n");
exit(1);
          }
        }
      else if (use32Bits) {
        Asm("          inc   r7                      ; Point to expression result");
        Asm("          glo   r7");
        Asm("          plo   rf");
        Asm("          ghi   r7");
        Asm("          phi   rf");
        Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
        Asm("          phi   rd");
        Asm("          ldi   [iobuffer].0");
        Asm("          plo   rd");
        Asm("          sep   scall                   ; Display integer value");
        Asm("          dw    itoa32");
        Asm("          ldi   [iobuffer].1            ; Display result");
        Asm("          phi   rf");
        Asm("          ldi   [iobuffer].0");
        Asm("          plo   rf");
        Asm("          sep   scall");
        Asm("          dw    f_msg");
        Asm("          inc   r7                      ; Remove expression result");
        Asm("          inc   r7");
        Asm("          inc   r7");
        }
      else {
        Asm("          inc   r7                      ; Recover expression result");
        Asm("          lda   r7");
        Asm("          plo   rc");
        Asm("          ldn   r7");
        Asm("          phi   rc");
        Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
        Asm("          phi   rd");
        Asm("          ldi   [iobuffer].0");
        Asm("          plo   rd");
        Asm("          sep   scall                   ; Display integer value");
        Asm("          dw    itoa");
        Asm("          ldi   [iobuffer].1            ; Display result");
        Asm("          phi   rf");
        Asm("          ldi   [iobuffer].0");
        Asm("          plo   rf");
        Asm("          sep   scall");
        Asm("          dw    f_msg");
        }
      last = ' ';
      }
    line=trim(line);
    }
  if (last != ';' && last != ',') {
    Asm("          sep   scall                   ; Display cr/lf");
    Asm("          dw    f_inmsg");
    Asm("          db    10,13,0");
    }
  return line;
  }

