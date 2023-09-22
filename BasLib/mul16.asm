#include    macros.inc
#include    bios.inc

            proc    mul16

            extrn   mdnorm

            sex     r7
            irx
            ldxa
            plo     rd
            ldxa
            phi     rd
            ldxa
            plo     rc
            ldx
            phi     rc
            sex     r2
            sep     scall
            dw      mdnorm
            plo     re
            ldi     0
            phi     rf
            plo     rf
mulloop:    glo     rd
            lbnz    mulcont
            ghi     rd
            lbnz    mulcont
            glo     re
            shr
            lbnf    mulexit
            glo     rf
            xri     0ffh
            plo     rf
            ghi     rf
            xri     0ffh
            phi     rf
            inc     rf
mulexit:    sex     r7
            ghi     rf
            stxd
            glo     rf
            stxd
            sex     r2
            sep     sret
mulcont:    ghi     rd
            shr
            phi     rd
            glo     rd
            shrc
            plo     rd
            lbnf    mulcont2
            glo     rc
            str     r2
            glo     rf
            add
            plo     rf
            ghi     rc
            str     r2
            ghi     rf
            adc
            phi     rf
mulcont2:   glo     rc
            shl
            plo     rc
            ghi     rc
            shlc
            phi     rc
            lbr     mulloop

            endp

