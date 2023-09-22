#include    macros.inc
#include    bios.inc

; ***********************************
; ***** Copy inline string      *****
; ***** RD - destination string *****
; ***** RF - source string      *****
; ***********************************
            proc    strcpyin

            lda     r6           ; get byte from source string
            str     rd           ; store into destination
            inc     rd
            lbnz    strcpyin     ; loop back until terminator copied
            sep     sret         ; return to caller

            endp

