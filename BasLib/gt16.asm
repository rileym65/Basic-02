#include    macros.inc
#include    bios.inc

            proc    gt16

            extrn   sub16
            extrn   true
            extrn   false

            sep     scall
            dw      sub16
            sex     r7
            irx
            ldxa
            or
            sex     r2
            lbz     false
            ldn     r7
            shl
            lbnf    true
            lbr     false

            endp

