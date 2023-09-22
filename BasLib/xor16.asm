#include    macros.inc
#include    bios.inc

            proc    xor16

            sex     r7
            irx
            ldxa
            irx
            xor
            stxd
            ldxa
            irx
            xor
            stxd
            dec     r7
            sex     r2
            sep     sret

            endp

