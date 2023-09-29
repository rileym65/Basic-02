#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** Set string                       ***** 
; ***** RD - destination string variable ***** 
; ***** RF - source string variable      ***** 
; ******************************************** 
            proc    assignstring

            extrn   dealloc

            lda     rd           ; need to see if string needs deallocation
            str     r2           ; save for combine
            ldn     rd           ; get lsb of address
            dec     rd           ; put rd back
            or                   ; combine with high byte
            lbz     empty        ; jump if no deallocation needed
            push    rf           ; save source string
            lda     rd           ; get address of string data
            phi     rf
            ldn     rd           ; low byte of address
            plo     rf
            dec     rd           ; move rd back
            call    dealloc      ; deallocate memory
            pop     rf           ; recover source string
empty:      lda     rf           ; transfer address of data
            str     rd
            inc     rd
            ldn     rf
            str     rd
            ldi     0            ; then deassign from source
            str     rf
            dec     rf
            str     rf
            rtn 

            endp

