#include    macros.inc
#include    bios.inc

; ********************************** 
; ***** String length          ***** 
; ***** RF - pointer to string ***** 
; ***** Returns: RC - length   ***** 
; ********************************** 
            proc    strlen

            ldi     0            ; set count to zero
            plo     rc
            phi     rc
strlen_1:   lda     rf           ; get byte from string
            lbz     strlen_2     ; jump if terminator found
            inc     rc           ; otherwise increment count
            lbr     strlen_1     ; and keep looking
strlen_2:   sep     sret         ; return to caller

            endp

