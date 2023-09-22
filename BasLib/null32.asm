#include    macros.inc
#include    bios.inc

; *************************************** 
; ***** M[RA] = 0                   ***** 
; *************************************** 
            proc     null32

            ldi      0                 ; need to zero
            str      ra                ; store to lsb
            inc      ra                ; point to second byte
            str      ra                ; store to second byte
            inc      ra                ; point to third byte
            str      ra                ; store to third byte
            inc      ra                ; point to msb
            str      ra                ; store to msb
            dec      ra                ; restore rf
            dec      ra
            dec      ra
            sep      sret              ; return to caller

            endp

