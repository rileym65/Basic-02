#include    macros.inc
#include    bios.inc

; *********************************** 
; ***** Concatenate string      ***** 
; ***** RD - destination string ***** 
; ***** RF - source string      ***** 
; *********************************** 
            proc    strcat

            extrn   strcpy

            lda     rd           ; look for terminator
            lbnz    strcat       ; loop back until terminator found
            dec     rd           ; move back to terminator
            lbr     strcpy       ; and then copy source string to end

            endp

