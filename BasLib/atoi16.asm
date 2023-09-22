#include    macros.inc
#include    bios.inc

; **************************************** 
; ***** Convert ASCII to integer     ***** 
; ***** RF - Pointer to ASCII number ***** 
; ***** Returns: RC - 16-bit integer ***** 
; **************************************** 
            proc    atoi

            ldi     0
            plo     rc
            phi     rc
            plo     r9
            ldn     rf
            smi     '-'
            lbnz    atoi_0_1
            inc     rf
            inc     r9
atoi_0_1:   lda     rf
            plo     re
            smi     '0'
            lbnf    atoi_no
            smi     10
            lbnf    atoi_0_2
atoi_no:    glo     r9
            shr
            lbnf    atoi_rt
            glo     rc
            xri     0ffh
            adi     1
            plo     rc
            ghi     rc
            xri     0ffh
            adci    0
            phi     rc
atoi_rt:    sep     sret
atoi_0_2:   glo     re
            smi     '0'
            plo     re
            glo     rc
            shl
            plo     rc
            plo     r8
            ghi     rc
            shlc
            phi     rc
            phi     r8
            glo     r8
            shl
            plo     r8
            ghi     r8
            shlc
            phi     r8
            glo     r8
            shl
            plo     r8
            ghi     r8
            shlc
            phi     r8
            glo     r8
            str     r2
            glo     rc
            add
            plo     rc
            ghi     r8
            str     r2
            ghi     rc
            adc
            phi     rc
            glo     re
            str     r2
            glo     rc
            add
            plo     rc
            ghi     rc
            adci    0
            phi     rc
            lbr     atoi_0_1

            endp

