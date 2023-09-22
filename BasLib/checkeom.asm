#include    macros.inc
#include    bios.inc

; *********************************** 
; ***** Check for out of memory ***** 
; *********************************** 
            proc    checkeom

            extrn   HEAP_
            extrn   FREE_

            ghi     rc                  ; save consumed register
            stxd
            glo     rc
            stxd
            ldi     FREE_.0             ; get end of variable table
            plo     r9
            ldi     FREE_.1
            phi     r9
            lda     r9                  ; retrieve variable table end
            phi     rc
            lda     r9
            plo     rc
            ldi     HEAP_.0             ; point to heap start
            plo     r9
            ldi     HEAP_.1
            phi     r9
            inc     r9                  ; point to lsb
            ldn     r9                  ; get heap
            str     r2
            glo     rc                  ; subtract from variable table end
            sm
            dec     r9                  ; point to msb
            ldn     r9                  ; retrieve it
            str     r2
            ghi     rc                  ; subtract from variable table end
            smb
            lbdf    oom                 ; jump of out of memory
            irx                         ; recover consumed register
            ldxa
            plo     rc
            ldx
            phi     rc
            sep     sret                ; and return to caller
oom:        sep     scall               ; display out of memory error
            dw      f_inmsg
            db      'Out of memory: ',0
            lbr     $                   ; show line of error and exit

            endp

