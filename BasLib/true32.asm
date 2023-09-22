#include    macros.inc
#include    bios.inc

            proc    true32

            ldi     0ffh
            sex     r7
            stxd
            stxd
            stxd
            stxd
            sex     r2
            sep     sret

            endp

