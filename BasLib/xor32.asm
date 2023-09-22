#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit Xor. expr stack               ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ************************************************ 
            proc     xor32

            inc      r7                ; point to second number
            glo      r7                ; copy address to rf
            plo      rf
            ghi      r7
            phi      rf
            inc      rf                ; point rf to first number
            inc      rf
            inc      rf
            inc      rf
            sex      rf                ; point X to destination
            lda      r7                ; get byte 1
            xor                        ; and with first number
            str      rf                ; store
            inc      rf                ; point to byte 2
            lda      r7                ; get byte 2
            xor                        ; and with first number
            str      rf                ; store
            inc      rf                ; point to byte 3
            lda      r7                ; get byte 3
            xor                        ; and with first number
            str      rf                ; store
            inc      rf                ; point to byte 4
            ldn      r7                ; get byte 7
            xor                        ; and with first number
            str      rf                ; store
            sex      r2                ; Set x back to R2
            sep      sret              ; return to caller

            endp

