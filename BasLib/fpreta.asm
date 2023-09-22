#include    macros.inc
#include    bios.inc

            proc    fpret_a

            irx                  ; recover destination address
            ldxa
            plo     rf
            ldx
            phi     rf
            glo     r8           ; store a as answer
            str     rf
            inc     rf
            ghi     r8
            str     rf
            inc     rf
            glo     r7
            str     rf
            inc     rf
            ghi     r7
            str     rf
            irx
            ldxa
            plo     r7
            ldx
            phi     r7
            sep     sret         ; and return to caller

            endp

