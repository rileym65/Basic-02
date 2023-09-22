#include    macros.inc
#include    bios.inc

; ********************************************* 
; ***** String compare                    ***** 
; ***** RF - string1                      ***** 
; ***** RD - string2                      ***** 
; ***** Returns: DF=0 - strings unequal   ***** 
; *****          DF=1 - strings equal     ***** 
; *****          D=1  - string1 > string2 ***** 
; *****          D=0  - string1 < string2 ***** 
; ********************************************* 
            proc    strcmp

            lda     rf           ; get byte from string1
            str     r2
            lbnz    strcmp_1     ; jump if terminator not found
            lda     rd           ; get byte from second string
            lbz     strcmp_eq    ; jump if strings are equal
            lbr     strcmp_lt    ; jump if string1 is smaller
strcmp_1:   lda     rd           ; get byte from second string
            lbz     strcmp_gt    ; jump if string2 is lower
            sd                   ; subtract from first string
            lbz     strcmp       ; loop to check remaining bytes
            lbdf    strcmp_gt    ; jump if
strcmp_lt:  ldi     0            ; signal string 1 is lower
            lbr     strcmp_rt
strcmp_eq:  ldi     1            ; signal strings equal
            lbr     strcmp_rt
strcmp_gt:  ldi     2            ; signal string 2 is lower
strcmp_rt:  shr
            sep     sret

            endp

