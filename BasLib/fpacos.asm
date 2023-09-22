#include    macros.inc
#include    bios.inc

; ****************************************************** 
; ***** Compute arcsin                             ***** 
; ****************************************************** 
            proc    fpacos

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
            sex     r7           ; now place 1.0
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
            ldi     03fh         ; now place 1.0
            stxd
            ldi     080h
            stxd
            ldi     000h
            stxd
            stxd
            ghi     r9           ; and 1 more x
            stxd
            glo     r9
            stxd
            ghi     r8
            stxd
            glo     r8
            stxd
            sex     r2
            sep     scall        ; add 1 to x
            dw      addfp
            inc     r7           ; transfer 1+x to stack for safe keeping
            lda     r7
            stxd
            lda     r7
            stxd
            lda     r7
            stxd
            ldn     r7
            stxd
            sep     scall        ; multiply the two xs
            dw      mulfp
            sep     scall        ; subtract from 1.0
            dw      subfp
            sep     scall        ; take the square root
            dw      fpsqrt
            irx                  ; transfer 1+x back to expr stack
            ldxa
            str     r7
            dec     r7
            ldxa
            str     r7
            dec     r7
            ldxa
            str     r7
            dec     r7
            ldx
            str     r7
            dec     r7
            sep     scall        ; now divide
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

