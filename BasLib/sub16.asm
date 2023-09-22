#include    macros.inc
#include    bios.inc

            proc    sub16

            sex     r7
            irx
            ldxa
            irx
            sd
            stxd
            ldxa
            irx           
            sdb
            stxd
            dec     r7
            sex     r2
            sep     sret

            endp

