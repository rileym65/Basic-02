#include    macros.inc
#include    bios.inc

            proc    sgnfp

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
            lbdf    sgnmfp
            ldn     r7
            or
            lbz     sgn0fp
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
sgnmfp:     ldi     0ffh
            str     r7
            dec     r7
            str     r7
            dec     r7
            str     r7
            dec     r7
            str     r7
            dec     r7
            sep     sret
sgn0fp:     dec     r7
            dec     r7
            dec     r7
            dec     r7
            sep     sret

            endp

