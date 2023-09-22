#include    macros.inc
#include    bios.inc

; ********************************************* 
; ***** Return amount of free heap memory ***** 
; ***** Returns: RC - free heap memory    ***** 
; ********************************************* 
            proc    hfree

            extrn   HEAP_

            ldi     0                   ; clear count
            plo     rc
            phi     rc
            ldi     HEAP_.0             ; setup heap pointer
            plo     r9
            ldi     HEAP_.1
            phi     r9
            lda     r9                  ; retrieve start of heap
            phi     rf
            ldn     r9
            plo     rf
hfree_lp:   lda     rf                  ; get heap allocation status byte
            lbz     hfree_dn            ; jump if end of heap
            plo     re                  ; save this for a moment
            lda     rf                  ; retrieve block size
            phi     rd
            lda     rf
            plo     rd
            str     r2                  ; add size to block address
            glo     rf
            add
            plo     rf
            ghi     rd
            str     r2
            ghi     rf
            adc
            phi     rf
            glo     re                  ; recover status byte
            smi     1                   ; is it a free block
            lbnz    hfree_lp            ; jump if not
            glo     rd                  ; add block size to count
            str     r2
            glo     rc
            add
            plo     rc
            ghi     rd
            str     r2
            ghi     rc
            adc
            phi     rc
            lbr     hfree_lp            ; check next block
hfree_dn:   sep     sret                ; and return

            endp

