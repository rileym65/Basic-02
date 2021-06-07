#include "header.h"

char* clocate(char* line) {
  int  pos;
  word addr;
  Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
  Asm("          phi   rd");
  Asm("          ldi   [iobuffer].0");
  Asm("          plo   rd");
  Asm("          ldi   27                      ; initial portion of escape sequence");
  Asm("          str   rd");
  Asm("          inc   rd");
  Asm("          ldi   '['");
  Asm("          str   rd");
  Asm("          inc   rd");
  line = cexpr(line);
  line = trim(line);
  if (*line != ',') {
    showError("Syntax error");
    exit(1);
    }
  line++;
  Asm("          inc   r7                      ; Get row");
  Asm("          lda   r7");
  Asm("          plo   rc");
  Asm("          ldn   r7");
  Asm("          phi   rc");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  Asm("          ldi   [iobuffer]+2.1          ; Point to i/o buffer");
  Asm("          phi   rd");
  Asm("          ldi   [iobuffer]+2.0");
  Asm("          plo   rd");
  Asm("          sep   scall                   ; Send row");
  Asm("          dw    itoa");
  Asm("          ldi   ';'                     ; Next need a semicolon");
  Asm("          str   rd");
  Asm("          inc   rd");
  Asm("          ghi   rd                      ; Save rd");
  Asm("          stxd");
  Asm("          glo   rd");
  Asm("          stxd");
  line = cexpr(line);
  Asm("          irx                           ; Recover RD");
  Asm("          ldxa");
  Asm("          plo   rd");
  Asm("          ldx");
  Asm("          phi   rd");
  Asm("          inc   r7                      ; Get column");
  Asm("          lda   r7");
  Asm("          plo   rc");
  Asm("          ldn   r7");
  Asm("          phi   rc");
  if (use32Bits) {
    Asm("          inc   r7                      ; Remove high word");
    Asm("          inc   r7");
    }
  Asm("          sep   scall                   ; Send column");
  Asm("          dw    itoa");
  Asm("          ldi   'H'                     ; Lastly need an H");
  Asm("          str   rd");
  Asm("          inc   rd");
  Asm("          ldi   0                       ; terminate string");
  Asm("          str   rd");
  Asm("          ldi   [iobuffer].1            ; Point to i/o buffer");
  Asm("          phi   rf");
  Asm("          ldi   [iobuffer].0");
  Asm("          plo   rf");
  Asm("          sep   scall                   ; Send position escape sequcne");
  Asm("          dw    f_msg");
  return line;
  }

