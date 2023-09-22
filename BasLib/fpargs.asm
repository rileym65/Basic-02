#include    macros.inc
#include    bios.inc

; ********************************* 
; ***** Retrieve fp arguments ***** 
; ***** M[RF] -> R7:R8 R9.0   ***** 
; ***** M[RD] -> RA:RB R9.1   ***** 
; ********************************* 
            proc    fpargs

            lda     rf           ; retrieve first number
            plo     r8
            lda     rf
            phi     r8
            lda     rf
            plo     r7
            shl                  ; shift low bit of exponent
            lda     rf
            phi     r7
            shlc                 ; get full exponent
            plo     r9           ; save exponent 1
            lda     rd           ; retrieve second number
            plo     rb
            lda     rd
            phi     rb
            lda     rd
            plo     ra
            shl                  ; shift low bit of exponent
            lda     rd
            phi     ra
            shlc                 ; get full exponent
            phi     r9           ; save exponent 2
            sep     sret         ; return to caller

            endp

