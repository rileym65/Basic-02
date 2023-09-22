#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit cmp.  M[RF]-M[RD]             ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ***** Returns: D=0 if M[RF]=M[RD]          ***** 
; *****          DF=1 if M[RF]<M[RD]         ***** 
; ************************************************ 
            proc     comp32

            lda      rd                ; get lsb from second number
            str      r2                ; store for subtract
            lda      rf                ; get lsb from first number
            sm                         ; subtract
            plo      re                ; save as zero test
            lda      rd                ; get 2nd byte of second number
            str      r2                ; store for subtract
            lda      rf                ; get 2nd byte of first number
            smb                        ; perform subtraction
            str      r2                ; store for combining with zero test
            glo      re                ; get zero test
            or                         ; or last result
            plo      re                ; and put back
            lda      rd                ; get 3rd byte of second number
            str      r2                ; store for subtract
            lda      rf                ; get 3rd byte of first number
            smb                        ; perform subtraction
            str      r2                ; store for combining with zero test
            glo      re                ; get zero test
            or                         ; or last result
            plo      re                ; and put back
            ldn      rd                ; get msb of second number
            str      r2                ; store for subtract
            ldn      rf                ; get msb of first number
            smb                        ; perform subtraction
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

