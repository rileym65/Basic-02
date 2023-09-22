#include    macros.inc
#include    bios.inc

; ***************************************** 
; ***** Middle portion of string      ***** 
; ***** RF - pointer to source string ***** 
; ***** RD - pointer to destination   ***** 
; ***** RB - Starting point           ***** 
; ***** RC - Count of characters      ***** 
; ***************************************** 
            proc    mid

            extrn   left

            glo     rb           ; see if starting position found
            str     r2
            ghi     rc
            or
            lbz     mid_2        ; use left to copy characters
            dec     rb           ; decrement count
            lda     rf           ; get byte from source string
            lbz     mid_dn       ; jump if terminator found, will be empty destination
            lbr     mid          ; keep looping until start point
mid_dn:     ldi     0            ; write terminator to destination
            str     rd
            sep     sret         ; and return
mid_2:      sep     scall        ; call left to copy characters
            dw      left
            sep     sret         ; and return to caller

            endp

