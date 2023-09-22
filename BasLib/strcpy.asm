#include    macros.inc
#include    bios.inc

; *********************************** 
; ***** Copy string             ***** 
; ***** RD - destination string ***** 
; ***** RF - source string      ***** 
; *********************************** 
            proc    strcpy

            lda     rf           ; get byte from source string
            str     rd           ; store into destination
            inc     rd
            lbnz    strcpy       ; loop back until terminator copied
            sep     sret         ; return to caller

            endp

