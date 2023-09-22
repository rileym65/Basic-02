#include    macros.inc
#include    bios.inc

; *************************************** 
; ***** Convert string to uppercase ***** 
; ***** RF - Pointer to string      ***** 
; *************************************** 
            proc    upper

            ldn     rf           ; get byte from buffer
            lbz     return       ; jump if terminator found
            smi     'a'          ; Check for lower range
            lbnf    uppernxt     ; jump if below range
            smi     26           ; check for above range
            lbdf    uppernxt     ; jump if above range
            ldn     rf           ; get character
            smi     32           ; convert to lowercvase
            str     rf           ; and put it back
uppernxt:   inc     rf           ; point to next character
            lbr     upper        ; process rest of string
return:     sep     sret

            endp
