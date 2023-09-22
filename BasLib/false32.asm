#include    macros.inc
#include    bios.inc

            proc    false32

            ldi     000h
            sex     r7
            stxd
            stxd
            stxd
            stxd
            sex     r2
            sep     sret

            endp

