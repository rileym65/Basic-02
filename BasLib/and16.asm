#include    macros.inc
#include    bios.inc

            proc    and16

            sex     r7
            irx
            ldxa
            irx
            and
            stxd
            ldxa
            irx
            and
            stxd
            dec     r7
            sex     r2
            sep     sret

            endp

