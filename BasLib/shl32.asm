#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit shift left.  M[RA]=M[RA]<<1   ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ************************************************ 
            proc     shl32

            ldn      ra                ; get lsb
            shl                        ; shift it
            str      ra                ; put it back
            inc      ra                ; point to second byte
            ldn      ra                ; get it
            shlc                       ; shift it
            str      ra
            inc      ra                ; point to third byte
            ldn      ra                ; get it
            shlc                       ; shift it
            str      ra
            inc      ra                ; point to msb
            ldn      ra                ; get it
            shlc                       ; shift it
            str      ra
            dec      ra                ; restore rf
            dec      ra
            dec      ra
            sep      sret              ; and return

            endp

