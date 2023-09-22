#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** Natural exp                                ***** 
; ***** RF - Pointer to floating point number      ***** 
; ***** RD - Pointer to floating point destination ***** 
; ***** internal:                                  ***** 
; *****       R2+1     - sum                       ***** 
; *****       R2+5     - last                      ***** 
; *****       R2+9     - fct                       ***** 
; *****       R2+13    - fctCount                  ***** 
; *****       R2+17    - pwr                       ***** 
; *****       R2+21    - tmp                       ***** 
; *****       R2+25    - n                         ***** 
; ****************************************************** 
            proc     fpexp

.link .requires fpdata

            extrn    addtows
            extrn    getargs
            extrn    addfpi
            extrn    mulfpi
            extrn    divfpi
            extrn    fp_0
            extrn    fp_1
            extrn    fp_2

            ghi      r7           ; save expr stack
            stxd
            glo      r7
            stxd
            ghi      r7           ; source is expr stack
            phi      rf
            glo      r7
            plo      rf
            inc      rf
            ghi      rf           ; n = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            stxd                  ; space for tmp
            stxd
            stxd
            stxd
            ghi      rf           ; pwr = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ldi      fp_2.1       ; fctCount = 2.0
            phi      rd
            ldi      fp_2.0
            plo      rd
            sep      scall
            dw       addtows
            ldi      fp_1.1       ; fct = 1.0
            phi      rd
            ldi      fp_1.0
            plo      rd
            sep      scall
            dw       addtows
            ldi      fp_0.1       ; last = 0
            phi      rd
            ldi      fp_0.0
            plo      rd
            sep      scall
            dw       addtows
            ghi      rf           ; sum = argument
            phi      rd
            glo      rf
            plo      rd
            sep      scall
            dw       addtows
            ghi      r2           ; sum = sum + 1
            phi      rf
            glo      r2
            plo      rf
            inc      rf
            ldi      fp_1.1
            phi      rd
            ldi      fp_1.0
            plo      rd
            sep      scall
            dw       addfpi
fpexp_l:    sep      scall        ; need to see if sum == last
            dw       getargs
            db       5,1
            ldi      4            ; 4 bytes to check
            plo      rc
            ldi      0            ; clear comparison flag
            plo      re
fpexp_1:    ldn      rd           ; get byte from sum
            str      r2           ; save for comparison
            ldn      rf           ; get point from last
            sm                    ; compare them
            str      r2           ; store to combine with comparison flag
            glo      re           ; get comparison flag
            or                    ; combine
            plo      re           ; put back into comparison
            ldn      rd           ; get byte from sum
            str      rf           ; store into last
            inc      rd           ; increment pointers
            inc      rf
            dec      rc           ; decrement count
            glo      rc           ; see if done
            lbnz     fpexp_1      ; jump if not
            glo      re           ; get comparison flag
            lbz      fpexp_d      ; jump if done
            sep      scall        ; pwr = pwr * n
            dw       getargs
            db       17,25
            sep      scall
            dw       mulfpi
            sep      scall        ; fct = fct * fctCount
            dw       getargs
            db       9,13
            sep      scall
            dw       mulfpi
            glo      r2           ; fctCount = fctCount + 1
            adi      13
            plo      rf
            ghi      r2
            adci     0
            phi      rf
            ldi      fp_1.1
            phi      rd
            ldi      fp_1.0
            plo      rd
            sep      scall
            dw       addfpi
            sep      scall        ; tmp = pwr
            dw       getargs
            db       21,17
            lda      rd
            str      rf
            inc      rf
            lda      rd
            str      rf
            inc      rf
            lda      rd
            str      rf
            inc      rf
            lda      rd
            str      rf
            sep      scall        ; tmp = tmp / fct
            dw       getargs
            db       21,9
            sep      scall
            dw       divfpi
            sep      scall        ; sum = sum + tmp
            dw       getargs
            db       1,21
            sep      scall
            dw       addfpi
            lbr      fpexp_l      ; loop until done
fpexp_d:    irx                   ; recover answer
            ldxa
            plo      r8
            ldxa
            phi      r8
            ldxa
            plo      ra
            ldx
            phi      ra
            glo      r2           ; clean workspace off stack
            adi      24
            plo      r2
            ghi      r2
            adci     0
            phi      r2
            irx                   ; recover expr stack
            ldxa
            plo      r7
            ldx
            phi      r7
            inc      r7
            glo      r8           ; store answer
            str      r7
            inc      r7
            ghi      r8
            str      r7
            inc      r7
            glo      ra
            str      r7
            inc      r7
            ghi      ra
            str      r7
            dec      r7
            dec      r7
            dec      r7
            dec      r7
            sep      sret         ; and return to caller

            endp

