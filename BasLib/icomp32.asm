#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit cmp.  M[RD]-M[RF]             ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ***** Returns: D=0 if M[RD]=M[RF]          ***** 
; *****          DF=1 if M[RD]<M[RF]         ***** 
; ************************************************ 
            proc     icomp32

            lda      rd                ; get lsb from second number
            str      r2                ; store for subtract
            lda      rf                ; get lsb from first number
            sd                         ; subtract
            plo      re                ; save as zero test
            lda      rd                ; get 2nd byte of second number
            str      r2                ; store for subtract
            lda      rf                ; get 2nd byte of first number
            sdb                        ; perform subtraction
            str      r2                ; store for combining with zero test
            glo      re                ; get zero test
            or                         ; or last result
            plo      re                ; and put back
            lda      rd                ; get 3rd byte of second number
            str      r2                ; store for subtract
            lda      rf                ; get 3rd byte of first number
            sdb                        ; perform subtraction
            str      r2                ; store for combining with zero test
            glo      re                ; get zero test
            or                         ; or last result
            plo      re                ; and put back
            ldn      rd                ; get msb of second number
            str      r2                ; store for subtract
            ldn      rf                ; get msb of first number
            sdb                        ; perform subtraction
            str      r2                ; store for combining with zero test
            shl                        ; shift sign bit into df
            glo      re                ; get zero test
            or                         ; or last result
            dec      rf                ; restore registers
            dec      rf
            dec      rf
            dec      rd
            dec      rd
            dec      rd
            sep      sret              ; return to caller

            endp

