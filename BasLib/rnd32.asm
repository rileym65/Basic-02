#include    macros.inc
#include    bios.inc

            proc    rnd32

            extrn   lfsr_lp
            extrn   mod32
            extrn   LFSR_

            ldi     32
            plo     rc
            sep     scall         ; Shift the register
            dw      lfsr_lp
            ldi     LFSR_.1
            phi     r9
            ldi     LFSR_.0
            plo     r9

            inc     r7            ; Retrieve range
            lda     r7
            plo     rb
            lda     r7
            phi     rb
            lda     r7
            plo     ra
            ldn     r7
            phi     ra

            lda     r9            ; Transfer random number
            ani     07fh          ; no negative numbers
            str     r7
            dec     r7
            lda     r9
            str     r7
            dec     r7
            lda     r9
            str     r7
            dec     r7
            lda     r9
            str     r7
            dec     r7

            ghi     ra            ; Put range on expr stack
            str     r7
            dec     r7
            glo     ra
            str     r7
            dec     r7
            ghi     rb
            str     r7
            dec     r7
            glo     rb
            str     r7
            dec     r7
            lbr     mod32          ; and perform modulo

            endp

