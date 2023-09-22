#include    macros.inc
#include    bios.inc

            proc    mulfp

            extrn   mulfpi

            glo     r7           ; Setup registers for call
            plo     rf
            plo     rd
            ghi     r7
            phi     rf
            phi     rd
            inc     rd
            inc     rf
            inc     rf
            inc     rf
            inc     rf
            inc     rf
            sep     scall        ; Call addition
            dw      mulfpi
            inc     r7           ; Adjust expr stack
            inc     r7
            inc     r7
            inc     r7
            sep     sret         ; And return

            endp

