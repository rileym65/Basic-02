#include    macros.inc
#include    bios.inc

            proc    or16

            sex     r7
            irx
            ldxa
            irx
            or
            stxd
            ldxa
            irx
            or
            stxd
            dec     r7
            sex     r2
            sep     sret

            endp

