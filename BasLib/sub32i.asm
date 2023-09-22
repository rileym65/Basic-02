#include    macros.inc
#include    bios.inc

; ************************************************ 
; ***** 32-bit subtract.  M[RF]=M[RF]-M[RD]  ***** 
; ***** Numbers in memory stored LSB first   ***** 
; ************************************************ 
            proc     sub32i

            sex      rd                ; point x to second number
            ldn      rf                ; get lsb
            sm                         ; subtract second lsb of second number
            str      rf                ; store it
            inc      rf                ; point to 2nd byte
            inc      rd
            ldn      rf                ; get second byte
            smb                        ; subtract second byte of second number
            str      rf                ; store it
            inc      rf                ; point to 3rd byte
            inc      rd
            ldn      rf                ; get third byte
            smb                        ; subtract third byte of second number
            str      rf                ; store it
            inc      rf                ; point to msb
            inc      rd
            ldn      rf                ; get msb byte
            smb                        ; subtract msb byte of second number
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

