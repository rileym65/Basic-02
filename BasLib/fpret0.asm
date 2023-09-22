#include    macros.inc
#include    bios.inc

            proc    fpret_0

            irx                  ; recover destination address
            ldxa
            plo     rf
            ldx
            phi     rf
            ldi     0            ; write 0
            str     rf
            inc     rf
            str     rf
            inc     rf
            str     rf
            inc     rf
            str     rf
            irx
            ldxa
            plo     r7
            ldx
            phi     r7
            sep     sret         ; and return

            endp

