#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** Square root                                ***** 
; ***** RF - Pointer to floating point number x    ***** 
; *****       R2+1     - x                         ***** 
; *****       R2+5     - s                         ***** 
; *****       R2+9     - p                         ***** 
; *****       R2+13    - arg                       ***** 
; ****************************************************** 
            proc     fpsqrt

.link .requires fpdata

            extrn    addtows
            extrn    getargs
            extrn    fpcopy
            extrn    addfpi
            extrn    mulfpi
            extrn    divfpi
            extrn    fpdot5

            ghi      r7           ; argument is on expr stack
            phi      rf
            glo      r7
            plo      rf
            inc      rf
            ghi      rf           ; arg = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ghi      rf           ; p = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ghi      rf           ; s = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ghi      rf           ; x = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ldi      255          ; set max iteration count
            plo      rc
fpsqrtlp:   sep      scall        ; x = arg
            dw       getargs
            db       1,13
            sep      scall
            dw       fpcopy
            glo      rc           ; save iteration count
            stxd
            sep      scall        ; x = x / s
            dw       getargs
            db       2,6
            sep      scall
            dw       divfpi
            sep      scall        ; s = s + x
            dw       getargs
            db       6,2
            sep      scall
            dw       addfpi
            glo      r2           ; s = s * 0.5
            adi      6
            plo      rf
            ghi      r2
            adci     0
            phi      rf
            ldi      fpdot5.1
            phi      rd
            ldi      fpdot5.0
            plo      rd
            sep      scall
            dw       mulfpi
            irx                   ; recover iteration count
            ldx
            plo      rc
            sep      scall        ; check p=s
            dw       getargs
            db       9,5
            lda      rf
            ani      0fch
            str      r2
            lda      rd
            ani      0fch
            sm
            lbnz     fpsqrtn
            lda      rf
            str      r2
            lda      rd
            sm
            lbnz     fpsqrtn
            lda      rf
            str      r2
            lda      rd
            sm
            lbnz     fpsqrtn
            lda      rf
            str      r2
            lda      rd
            sm
            lbz      fpsqrtd
fpsqrtn:    dec      rc           ; decrement iteration count
            glo      rc
            lbz      fpsqrtd      ; jump if reached
            sep      scall        ; p = s
            dw       getargs
            db       9,5
            sep      scall
            dw       fpcopy
            lbr      fpsqrtlp     ; loop until convergence
fpsqrtd:    irx                   ; retrieve answer
            irx
            irx
            irx
            irx
            ldxa
            plo      r8
            ldxa
            phi      r8
            ldxa
            plo      r9
            ldx
            phi      r9
            glo      r2           ; remove remaining workspace
            adi      8
            plo      r2
            ghi      r2
            adci     0
            phi      r2
            inc      r7
            glo      r8           ; store answer
            str      r7
            inc      r7
            ghi      r8
            str      r7
            inc      r7
            glo      r9
            str      r7
            inc      r7
            ghi      r9
            str      r7
            dec      r7
            dec      r7
            dec      r7
            dec      r7
            sep      sret         ; and return to caller

            endp

