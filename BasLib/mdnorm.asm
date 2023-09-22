#include    macros.inc
#include    bios.inc

            proc    mdnorm

            ghi     rc
            str     r2
            ghi     rd
            xor
            shl
            ldi     0
            shlc
            plo     re
            ghi     rc
            shl
            lbnf    mdnorm2
            ghi     rc
            xri     0ffh
            phi     rc
            glo     rc
            xri     0ffh
            plo     rc
            inc     rc
mdnorm2:    ghi     rd
            shl
            lbnf    mdnorm3
            ghi     rd
            xri     0ffh
            phi     rd
            glo     rd
            xri     0ffh
            plo     rd
            inc     rd
mdnorm3:    glo     re
            sep     sret

            endp
