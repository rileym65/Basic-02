#include    macros.inc
#include    bios.inc

; ***************************************** 
; ***** Convert RA:RB to bcd in M[RF] ***** 
; ***************************************** 
            proc    tobcd32

            glo     rf           ; transfer address to rc
            plo     rc
            ghi     rf
            phi     rc
            ldi     10           ; 10 bytes to clear
            plo     re
tobcd32lp1: ldi     0
            str     rc           ; store into answer
            inc     rc
            dec     re           ; decrement count
            glo     re           ; get count
            lbnz    tobcd32lp1   ; loop until done
            glo     rf           ; recover address
            plo     rc
            ghi     rf
            phi     rc
            ldi     32           ; 32 bits to process
            plo     r9
tobcd32lp2: ldi     10           ; need to process 5 cells
            plo     re           ; put into count
tobcd32lp3: ldn     rc           ; get byte
            smi     5            ; need to see if 5 or greater
            lbnf    tobcd32l3a   ; jump if not
            adi     8            ; add 3 to original number
            str     rc           ; and put it back
tobcd32l3a: inc     rc           ; point to next cell
            dec     re           ; decrement cell count
            glo     re           ; retrieve count
            lbnz    tobcd32lp3   ; loop back if not done
            glo     rb           ; start by shifting number to convert
            shl
            plo     rb
            ghi     rb
            shlc
            phi     rb
            glo     ra
            shlc
            plo     ra
            ghi     ra
            shlc
            phi     ra
            shlc                 ; now shift result to bit 3
            shl
            shl
            shl
            str     rc
            glo     rf           ; recover address
            plo     rc
            ghi     rf
            phi     rc
            ldi     10           ; 10 cells to process
            plo     re
tobcd32lp4: lda     rc           ; get current cell
            str     r2           ; save it
            ldn     rc           ; get next cell
            shr                  ; shift bit 3 into df
            shr
            shr
            shr
            ldn     r2           ; recover value for current cell
            shlc                 ; shift with new bit
            ani     0fh          ; keep only bottom 4 bits
            dec     rc           ; point back
            str     rc           ; store value
            inc     rc           ; and move to next cell
            dec     re           ; decrement count
            glo     re           ; see if done
            lbnz    tobcd32lp4   ; jump if not
            glo     rf           ; recover address
            plo     rc
            ghi     rf
            phi     rc
            dec     r9           ; decrement bit count
            glo     r9           ; see if done
            lbnz    tobcd32lp2   ; loop until done
            sep     sret         ; return to caller

            endp

