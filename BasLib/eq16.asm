#include    macros.inc
#include    bios.inc

            proc    eq16

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
            lbz     true
            lbr     false

            endp

