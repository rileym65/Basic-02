#include    macros.inc
#include    bios.inc

            proc    mod32

            extrn   div32

            sep     scall
            dw      div32
            inc     r7
            inc     r7
            inc     r7
            inc     r7
            ghi     ra
            str     r7
            dec     r7
            glo     ra
            str     r7
            dec     r7
            ghi     rb
            str     r7
            dec     r7
            glo     rb
            str     r7
            dec     r7
            sep     sret

            endp

