#include    macros.inc
#include    bios.inc

            proc    sgn32

            inc     r7
            lda     r7
            str     r2
            lda     r7
            or
            str     r2
            lda     r7
            or
            str     r2
            ldn     r7
            shl
            lbdf    sgnm32
            ldn     r7
            or
            lbz     sgn032
            ldi     0
            str     r7
            dec     r7
            str     r7
            dec     r7
            str     r7
            dec     r7
            ldi     1
            str     r7
            dec     r7
            sep     sret
sgnm32:     ldi     0ffh
            str     r7
            dec     r7
            str     r7
            dec     r7
            str     r7
            dec     r7
            str     r7
            dec     r7
            sep     sret
sgn032:     dec     r7
            dec     r7
            dec     r7
            dec     r7
            sep     sret

            endp

