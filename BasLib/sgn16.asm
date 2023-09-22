#include    macros.inc
#include    bios.inc

            proc    sgn16

            inc     r7
            lda     r7
            str     r2
            ldn     r7
            shl
            lbdf    sgnm
            ldn     r7
            or
            lbz     sgn0
            ldi     0
            str     r7
            dec     r7
            ldi     1
            str     r7
            dec     r7
            sep     sret
sgnm:       ldi     0ffh
            str     r7
            dec     r7
            str     r7
            dec     r7
            sep     sret
sgn0:       dec     r7
            dec     r7
            sep     sret

            endp

