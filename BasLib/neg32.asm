#include    macros.inc
#include    bios.inc

; ********************************************* 
; ***** 2s compliment the number in M[RA] ***** 
; ********************************************* 
            proc     neg32

            ldn      ra                ; get lsb
            xri      0ffh              ; invert it
            adi      1                 ; +1
            str      ra
            inc      ra                ; point to 2nd byte
            ldn      ra                ; retrieve it
            xri      0ffh              ; invert it
            adci     0                 ; propagate carry
            str      ra                ; and put back
            inc      ra                ; point to 3rd byte
            ldn      ra                ; retrieve it
            xri      0ffh              ; invert it
            adci     0                 ; propagate carry
            str      ra                ; and put back
            inc      ra                ; point to msb
            ldn      ra                ; retrieve it
            xri      0ffh              ; invert it
            adci     0                 ; propagate carry
            str      ra                ; and put back
            dec      ra                ; restore rf
            dec      ra
            dec      ra
            sep      sret              ; return

            endp

