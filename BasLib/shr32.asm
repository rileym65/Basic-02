#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit shift right. M[RA]=M[RA]>>1   ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ************************************************ 
            proc     shr32

            inc      ra                ; point to msb
            inc      ra
            inc      ra
            ldn      ra                ; get msb
            shr                        ; shift it right
            str      ra                ; put it back
            dec      ra                ; point to third byte
            ldn      ra                ; get third byte
            shrc                       ; shift it
            str      ra                ; put it back
            dec      ra                ; point to second byte
            ldn      ra                ; get second byte
            shrc                       ; shift it
            str      ra                ; put it back
            dec      ra                ; point to lsb
            ldn      ra                ; get lsb
            shrc                       ; shift it
            str      ra                ; put it back
            sep      sret              ; return to caller

            endp

