#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit multiply. M[RF]=M[RF]*M[RD]   ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ***** In routine:                          ***** 
; *****    R9 - points to first number       ***** 
; *****    RD - points to second number      ***** 
; *****    RF - points to answer             ***** 
; ************************************************ 
            proc     mul32i

            extrn    add32i
            extrn    shr32
            extrn    shl32
            extrn    zero32

            ldi      0                 ; need to zero answer
            stxd
            stxd
            stxd
            stxd
            glo      rf                ; r9 will point to first number
            plo      r9
            ghi      rf
            phi      r9
            glo      r2                ; rf will point to where the answer is
            plo      rf
            ghi      r2
            phi      rf
            inc      rf                ; point to LSB of answer
scmul2:     glo      rd                ; need second number
            plo      ra
            ghi      rd
            phi      ra
            sep      scall             ; check for zero
            dw       zero32
            lbnf     scmul4            ; jump if number was not zero
            inc      r2                ; now pointing at lsb of answer
            lda      r2                ; get number from stack
            str      r9                ; store into destination
            inc      r9                ; point to 2nd byte
            lda      r2                ; get number from stack
            str      r9                ; store into destination
            inc      r9                ; point to 3rd byte
            lda      r2                ; get number from stack
            str      r9                ; store into destination
            inc      r9                ; point to msb
            ldn      r2                ; get number from stack
            str      r9                ; store into destination
            sep      sret              ; return to caller
scmul4:     ldn      rd                ; get lsb of second number
            shr                        ; shift low bit into df
            lbnf     scmulno           ; no add needed
            ghi      rd                ; save position of second number
            stxd
            glo      rd
            stxd
            glo      r9                ; rd needs to be first number
            plo      rd
            ghi      r9
            phi      rd
            sep      scall             ; call add routine
            dw       add32i
            irx                        ; recover rd
            ldxa
            plo      rd
            ldx
            phi      rd
scmulno:    glo      r9                ; point to first number
            plo      ra
            ghi      r9
            phi      ra
            sep      scall             ; shift left
            dw       shl32
            glo      rd                ; now need pointer to second number
            plo      ra
            ghi      rd
            phi      ra
            sep      scall             ; shift right
            dw       shr32
            lbr      scmul2            ; loop until done

            endp

