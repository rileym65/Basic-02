#include    macros.inc
#include    bios.inc

            proc    mod16

            extrn   div16

            sep     scall
            dw      div16
            inc     r7
            inc     r7
            ghi     rc
            str     r7
            dec     r7
            glo     rc
            str     r7
            dec     r7
            sep     sret

            endp

