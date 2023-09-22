#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit Add.    M[RF]=M[RF]+M[RD]     ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ************************************************ 
            proc     add32i

            sex      rd                ; point x to second number
            ldn      rf                ; get lsb
            add                        ; add second lsb of second number
            str      rf                ; store it
            inc      rf                ; point to 2nd byte
            inc      rd
            ldn      rf                ; get second byte
            adc                        ; add second byte of second number
            str      rf                ; store it
            inc      rf                ; point to 3rd byte
            inc      rd
            ldn      rf                ; get third byte
            adc                        ; add third byte of second number
            str      rf                ; store it
            inc      rf                ; point to msb
            inc      rd
            ldn      rf                ; get msb byte
            adc                        ; add msb byte of second number
            str      rf                ; store it
            sex      r2                ; restore stack
            dec      rf                ; restore registers to original values
            dec      rf
            dec      rf
            dec      rd
            dec      rd
            dec      rd
            sep      sret              ; return to caller

            endp

