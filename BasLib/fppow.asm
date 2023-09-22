#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** Power x^y                                  ***** 
; ***** RF - Pointer to floating point number x    ***** 
; ***** RC - Pointer to floating point number y    ***** 
; ***** RD - Pointer to floating point destination ***** 
; ***** internal:                                  ***** 
; *****       R2+1     - x                         ***** 
; *****       R2+5     - y                         ***** 
; ****************************************************** 
            proc     fppow

            extrn    fpln
            extrn    mulfp
            extrn    fpexp

            inc      r7           ; x = log(x)
            inc      r7
            inc      r7
            inc      r7
            sep      scall
            dw       fpln
            dec      r7           ; now x = x * y
            dec      r7
            dec      r7
            dec      r7
            sep      scall
            dw       mulfp
            sep      scall        ; x = exp(x)
            dw       fpexp
            sep      sret         ; and return to caller

            endp

