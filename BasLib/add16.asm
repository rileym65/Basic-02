#include    macros.inc
#include    bios.inc

            proc    add16

            sex     r7
            irx
            ldxa
            irx
            add
            stxd
            ldxa
            irx           
            adc
            stxd
            dec     r7
            sex     r2
            sep     sret

            endp

