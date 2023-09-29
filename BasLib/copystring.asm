#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** copy string variable             ***** 
; ***** RD - destination string variable ***** 
; ***** RF - source string               ***** 
; ******************************************** 
            proc    copystring

            extrn   setstring

            lda     rf           ; get address from string variable
            plo     re           ; save msb
            ldn     rf           ; get lsb
            str     r2           ; store for zero check
            plo     rf           ; set rf to string data
            glo     re           ; set msb
            phi     rf
            or                   ; is there source data
            lbz     nosrc        ; jump if not
            lbr     setstring    ; otherwise copy string to desitnation
nosrc:      mov     rf,term      ; point to simple terminator
            lbr     setstring    ; and set string
term:       db      0

            endp

