#include    macros.inc
#include    bios.inc

; *************************************** 
; ***** is zero check               ***** 
; ***** returnss: DF=1 if M[RA]=0   ***** 
; *************************************** 
            proc     zero32

            sex      ra                ; point X to number
            ldxa                       ; get byte 0
            or                         ; combine with byte 1
            irx                        ; point to byte 2
            or                         ; combine
            irx                        ; point to byte 3
            or                         ; combine
            dec      ra                ; restore rf
            dec      ra
            dec      ra
            sex      r2                ; X back to 2
            lbnz     notzero           ; jump if not zero
            smi      0                 ; set df
            sep      sret              ; and return
notzero:    adi      0                 ; clear df
            sep      sret              ; and return

            endp

