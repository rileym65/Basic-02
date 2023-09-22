#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** cos                                        ***** 
; ***** RF - Pointer to floating point number      ***** 
; ***** RD - Pointer to floating point destination ***** 
; ***** internal:                                  ***** 
; *****       R2+1  R7 - sum                       ***** 
; *****       R2+5  R8 - pwr                       ***** 
; *****       R2+9  R9 - last                      ***** 
; *****       R2+13 RA - fctPos                    ***** 
; *****       R2+17 RB - fct                       ***** 
; *****       R2+21 RC - tmp                       ***** 
; *****       R2+25 RD - sgn                       ***** 
; *****       R2+29    - angle                     ***** 
; ****************************************************** 
            proc     fpcos

.link .requires fpsin
.link .requires fpdata

            extrn    addtows
            extrn    sincos
            extrn    fp_1
            extrn    fact

            ghi      r7           ; save expr stack
            stxd
            glo      r7
            stxd
            ghi      r7           ; source is expr stack
            phi      rf
            glo      r7
            plo      rf
            inc      rf
            ghi      rf           ; angle = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall        ; add to workspace
            dw       addtows
            ldi      0            ; sign starts out positive
            stxd                  ; make space for sgn
            stxd
            stxd
            stxd
            stxd                  ; make space for tmp
            stxd
            stxd
            stxd
            stxd                  ; make space for fct
            stxd
            stxd
            stxd
            stxd                  ; make space for fctPos
            stxd
            ldi      (fact+8).1   ; position of 2!
            stxd
            ldi      (fact+8).0
            stxd
            ldi      0
            stxd                  ; make space for last
            stxd
            stxd
            stxd
            ldi      fp_1.1       ; pwr = 1.0
            phi      rd
            ldi      fp_1.0
            plo      rd
            sep      scall        ; add to workspace
            dw       addtows
            ldi      fp_1.1       ; pwr = 1.0
            phi      rd
            ldi      fp_1.0
            plo      rd
            sep      scall        ; add to workspace
            dw       addtows
            lbr      sincos       ; now compute

            endp

