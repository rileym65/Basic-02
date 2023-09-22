#include    macros.inc
#include    bios.inc

            proc    gtefp

            extrn   subfp
            extrn   true32
            extrn   false32

            sep     scall
            dw      subfp
            sex     r7
            irx
            ldxa
            or
            ldxa
            or
            ldxa
            or
            ldx
            or
            sex     r2
            lbz     true32
            ldn     r7
            shl
            lbnf    true32
            lbr     false32

            endp

