#include    macros.inc
#include    bios.inc

            proc    abs16

            inc     r7
            inc     r7
            ldn     r7
            shl
            lbnf    absrt
            dec     r7
            ldn     r7
            xri     0ffh
            adi     1
            str     r7
            inc     r7
            ldn     r7
            xri     0ffh
            adci    0
            str     r7
absrt:      dec     r7
            dec     r7
            sep     sret

            endp

