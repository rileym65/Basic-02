#include    macros.inc
#include    bios.inc

; *********************************** 
; ***** Print string variable   ***** 
; ***** RD - string variable    ***** 
; ***** RF - Destination buffer ***** 
; *********************************** 
            proc    printstring

            lda     rd           ; need to see if string has data
            plo     re           ; save msb
            str     r2           ; save for combine
            ldn     rd           ; get lsb of address
            plo     rd           ; set rd to data address
            or                   ; combine with high byte
            lbz     empty        ; jump if no data
            glo     re           ; set msb of data
            phi     rd
copy:       lda     rd           ; copy character from string data
            str     rf           ; write to output buffer
            inc     rf
            lbnz    copy         ; keep copying until terminator copied
            rtn                  ; then return to caller
empty:      ldi     0            ; no data, so just write terminator
            str     rf
            rtn                  ; and return to caller

            endp

