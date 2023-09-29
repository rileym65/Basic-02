#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** Set string                       ***** 
; ***** RD - destination string variable ***** 
; ***** RF - source string               ***** 
; ******************************************** 
            proc    setstring

            extrn   alloc
            extrn   dealloc
            extrn   strlen
            extrn   strcpy

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
empty:      push    rf           ; save source string address
            call    strlen       ; get length of string
            inc     rc           ; plus 1 for terminator
            push    rd           ; save destination variable
            call    alloc        ; request memory
            pop     rd           ; recover destination variable
            ghi     rf           ; put memory address into variable
            str     rd
            inc     rd
            glo     rf           ; next low byte of address
            str     rd
            plo     rd           ; now set rd to destination string
            ghi     rf
            phi     rd
            pop     rf           ; recover source string
            lbr     strcpy       ; and copy

            endp

