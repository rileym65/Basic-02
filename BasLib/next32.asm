#include    macros.inc
#include    bios.inc

            proc    next32

            glo     r2
            plo     ra
            ghi     r2
            phi     ra
            sex     ra
            irx            ; return address lsb
            irx            ; return address msb
            irx            ; exec address lsb
            ldxa           ; retrieve exec address
            plo     r9
            ldxa
            phi     r9
            ldxa           ; get it
            plo     rf     ; set rf to address
            ldxa           ; get msb
            phi     rf
            inc     rf     ; point to variable lsb
            inc     rf     ; point to variable lsb
            inc     rf     ; point to variable lsb
            ldn     rf     ; retrieve it
            add            ; add in step
            str     rf
            dec     rf     ; point to byte2
            irx            ; point to byte2 of step
            ldn     rf     ; get byte2 of var value
            adc            ; add in step
            str     rf     ; store back into variable
            dec     rf     ; point to byte3
            irx            ; point to byte3 of step
            ldn     rf     ; get byte3 of var value
            adc            ; add in step
            dec     rf     ; point to byte4
            irx            ; point to byte4 of step
            ldn     rf     ; get byte3 of var value
            adc            ; add in step
            irx            ; point to loop count lsb
            ldi     1      ; need to decrement count
            sd             ; decrement it
            str     ra     ; and put it back
            irx            ; point to loop count byte2
            ldi     0      ; propagate carry
            sdb
            str     ra     ; and put it back
            irx            ; point to loop count byte3
            ldi     0      ; propagate carry
            sdb
            str     ra     ; and put it back
            irx            ; point to loop count byte4
            ldi     0      ; propagate carry
            sdb
            str     ra     ; and put it back
            sex     r2     ; point X back to R2
            lbdf    stay32 ; Jump if loop not done
            inc     r2
            dec     ra
            ldxa
            str     ra
            inc     ra
            ldx
            str     ra
            dec     ra
            dec     ra
            glo     ra
            plo     r2
            ghi     ra
            phi     r2
            sep     sret   ; nothing to do so return
stay32:     glo     r9     ; set return address to exec address
            plo     r6
            ghi     r9
            phi     r6
            sep     sret   ; and then return

            endp

