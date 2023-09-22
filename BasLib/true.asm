#include    macros.inc
#include    bios.inc

            proc    true

            ldi     0ffh
            sex     r7
            stxd
            stxd
            sex     r2
            sep     sret

            endp

