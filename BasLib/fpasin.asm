#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** Compute arcsin                             ***** 
; ****************************************************** 
            proc    fpasin

            extrn   addfp
            extrn   subfp
            extrn   mulfp
            extrn   divfp
            extrn   fpsqrt
            extrn   fpatan

            inc     r7           ; retrieve x
            lda     r7
            plo     r8
            lda     r7
            phi     r8
            lda     r7
            plo     r9
            ldn     r7
            phi     r9
            dec     r7           ; keep x on the expr stack
            dec     r7
            dec     r7
            dec     r7
            sex     r7           ; now place 2 1.0s
            ldi     03fh
            stxd
            ldi     080h
            stxd
            ldi     000h
            stxd
            stxd
            ldi     03fh
            stxd
            ldi     080h
            stxd
            ldi     000h
            stxd
            stxd
            ghi     r9           ; Put x back on the stack twice
            stxd
            glo     r9
            stxd
            ghi     r8
            stxd
            glo     r8
            stxd
            ghi     r9
            stxd
            glo     r9
            stxd
            ghi     r8
            stxd
            glo     r8
            stxd
            sex     r2
            sep     scall        ; x * x
            dw      mulfp
            sep     scall        ; subtract from 1.0
            dw      subfp
            sep     scall        ; take square root
            dw      fpsqrt
            sep     scall        ; add 1.0
            dw      addfp
            sep     scall        ; divide into x
            dw      divfp
            sep     scall        ; and then atan
            dw      fpatan
            sex     r7           ; multiply result by 2.0
            ldi     040h
            stxd
            ldi     000h
            stxd
            stxd
            stxd
            sex     r2
            sep     scall
            dw      mulfp
            sep     sret

            endp

