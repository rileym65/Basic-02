#include    macros.inc
#include    bios.inc

            proc    false

            ldi     000h
            sex     r7
            stxd
            stxd
            sex     r2
            sep     sret

            endp

