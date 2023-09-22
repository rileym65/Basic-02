#include macros.inc
#include bios.inc

; ***************************************** 
; ***** Right portion of string       ***** 
; ***** RF - pointer to source string ***** 
; ***** RD - pointer to destination   ***** 
; ***** RC - Count of characters      ***** 
; ***************************************** 
            proc    right

            extrn   strcpy

            ldi     0            ; zero counter
            plo     rb
            phi     rb
right_1:    lda     rf           ; get byte from source
            lbz     right_2      ; jump if terminator found
            inc     rb           ; increment length
            lbr     right_1      ; keep looking for terminator
right_2:    dec     rf           ; point back to previous character
            glo     rb           ; check RB counter
            str     r2
            ghi     rb
            or
            lbz     right_dn     ; start found, so now just copy
            glo     rc           ; check rc counter
            str     r2
            ghi     rc
            or
            lbz     right_dn     ; start found, so now just copy
            dec     rb           ; decrement counters
            dec     rc
            lbr     right_2      ; keep looking for start point
right_dn:   sep     scall        ; call strcpy to copy the string
            dw      strcpy
            sep     sret         ; and return

            endp

