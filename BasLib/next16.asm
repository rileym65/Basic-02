#include    macros.inc
#include    bios.inc

            proc    nextvar

            extrn   next

            irx          ; move to varAddr
            ldxa
            plo     rd
            ldxa
            phi     rd
            irx
            irx
            glo     rc   ; check for correct address
            sm           ; against stack
            lbnz    nv1  ; jump if not
            irx          ; move to msb
            ghi     rc
            sm           ; compare
            lbnz    nv2  ; jump if not
            dec     r2   ; entry found, move back
            dec     r2
            dec     r2
            dec     r2
            dec     r2
            dec     r2
            lbr     next
nv1:        irx          ; move past bad entry
nv2:        irx          ; move past bad entry
            irx       
            irx       
            irx       
            ghi     rd
            stxd
            glo     rd
            stxd
            lbr     nextvar

            endp

            proc    next

            glo     r2
            plo     ra
            ghi     r2
            phi     ra
            sex     ra
            irx          ; return address lsb
            irx          ; return address msb
            irx          ; exec address lsb
            ldxa         ; retrieve exec address
            plo     r9
            ldxa
            phi     r9
            ldxa         ; get it
            plo     rf   ; set rf to address
            ldxa         ; get msb
            phi     rf
            inc     rf   ; point to variable lsb
            ldn     rf   ; retrieve it
            add          ; add in step
            str     rf
            dec     rf   ; point to msb
            irx          ; point to msb of step
            ldn     rf   ; get msb of var value
            adc          ; add in step
            str     rf   ; store back into variable
            irx          ; point to loop count lsb
            ldi     1    ; need to decrement count
            sd           ; decrement it
            str     ra   ; and put it back
            irx          ; point to loop count msb
            ldi     0    ; propagate carry
            sdb
            str     ra   ; and put it back
            sex     r2   ; point X back to R2
            lbdf    stay ; Jump if loop not done
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
            sep     sret ; nothing to do so return
stay:       glo     r9   ; set return address to exec address
            plo     r6
            ghi     r9
            phi     r6
            sep     sret ; and then return

            endp

