#include    macros.inc
#include    bios.inc

; ***************************************** 
; ***** Left portion of string        ***** 
; ***** RF - pointer to source string ***** 
; ***** RD - pointer to destination   ***** 
; ***** RC - Count of characters      ***** 
; ***************************************** 
            proc    left

            glo     rc           ; see if characters left
            str     r2
            ghi     rc
            or
            lbz     left_dn      ; jump if not
            dec     rc           ; decrement count
            lda     rf           ; get byte from source
            str     rd           ; write into destination
            inc     rd
            lbnz    left         ; jump if terminator not found
left_rt:    sep     sret         ; otherwise return to caller
left_dn:    ldi     0            ; write terminator to destination
            str     rd
            lbr     left_rt      ; then return

            endp

