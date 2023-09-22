#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** Floating point subtraction       ***** 
; ***** RF - pointer to first fp number  ***** 
; ***** RD - pointer to second fp number ***** 
; ***** Uses: R7:R8 - first number (aa)  ***** 
; *****       RA:RB - second number (bb) ***** 
; *****       R9.0  - exponent           ***** 
; *****       R9.1  - sign               ***** 
; ******************************************** 
            proc    subfpi

.link .requires addfpi

            extrn   fpargs
            extrn   fpsub_1

            ghi     r7           ; save expr stack
            stxd
            glo     r7
            stxd
            ghi     rf           ; save destination address
            stxd
            glo     rf
            stxd
            sep     scall        ; retrieve arguments
            dw      fpargs
            ghi     ra           ; invert number
            xri     080h
            phi     ra           ; save inverted sign
            ghi     r9
            lbr     fpsub_1      ; now process with add

            endp

