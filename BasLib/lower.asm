#include    macros.inc
#include    bios.inc

; *************************************** 
; ***** Convert string to lowercase ***** 
; ***** RF - Pointer to string      ***** 
; *************************************** 
            proc    lower

            ldn     rf           ; get byte from buffer
            lbz     return       ; jump if terminator found
            smi     'A'          ; Check for lower range
            lbnf    lowernxt     ; jump if below range
            smi     26           ; check for above range
            lbdf    lowernxt     ; jump if above range
            ldn     rf           ; get character
            adi     32           ; convert to lowercvase
            str     rf           ; and put it back
lowernxt:   inc     rf           ; point to next character
            lbr     lower        ; process rest of string
return:     sep     sret

            endp

