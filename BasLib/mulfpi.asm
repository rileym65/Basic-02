#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** Floating point multiplication    ***** 
; ***** RF - pointer to first fp number  ***** 
; ***** RD - pointer to second fp number ***** 
; ***** Uses: R7:R8 - answer       (cc)  ***** 
; *****       RA:RB - second number (bb) ***** 
; *****       R9.0  - exponent           ***** 
; *****       R9.1  - sign               ***** 
; *****       RC:RD - first number (aa)  ***** 
; ******************************************** 
            proc    mulfpi

            extrn   fpnorm
            extrn   fpret_0
            extrn   fpret_a
            extrn   fpret_b

            ghi     r7           ; save expr stack
            stxd
            glo     r7
            stxd
            ghi     rf           ; save destination address
            stxd
            glo     rf
            stxd
            lda      rd           ; retrieve second number
            plo      rb           ; place into bb
            lda      rd
            phi      rb
            lda      rd
            plo      ra
            shl                   ; shift high bit into DF
            lda      rd
            phi      ra
            shlc                  ; now have full 8 bits of exponent
            phi      r9           ; store into r9
            lbz      fpret_0      ; jump if number is zero
            lda      rf           ; retrieve first number
            plo      rd           ; place into aa
            lda      rf
            phi      rd
            lda      rf
            plo      rc
            shl                   ; shift high bit into DF
            lda      rf
            phi      rc
            shlc                  ; now have exponent of first number
            plo      r9           ; save it
            lbz      fpret_0      ; jump if number was zero
            glo      r9           ; get exponent of first number
            smi      0ffh         ; check for infinity
            lbz      fpmul_a      ; jump if so
            ghi      r9           ; get exponent of second number
            smi      0ffh         ; check for infinity
            lbz      fpret_b      ; jump if so
            glo      r9           ; get exponent 1
            smi      127          ; remove bias
            str      r2           ; store for add
            ghi      r9           ; get exponent 2
            smi      127          ; remove bias
            add                   ; add in exponent 1
            adi      127          ; add bias back in
            plo      r9           ; r9 now has exponent of result
            ghi      ra           ; get msb of bb
            str      r2           ; store it
            ghi      rc           ; get msb of aa
            xor                   ; now have sign comparison
            shl                   ; shift sign into DF
            ldi      0            ; clear byte
            shlc                  ; shift in sign
            phi      r9           ; save sign for later
            ldi      0            ; need to clear high bytes
            phi      ra           ; of bb
            phi      rc           ; and aa
            plo      r8           ; also clear answer
            phi      r8
            plo      r7
            phi      r7
            glo      ra           ; get msb of bb mantissa
            ori      080h         ; add in implied 1
            plo      ra           ; and put it back
            glo      rc           ; get msb of aa mantissa
            ori      080h         ; add in implied 1
            plo      rc           ; and put it back
fpmul_lp:   glo      ra           ; need to zero check bb
            str      r2
            ghi      ra
            or
            str      r2
            glo      rb
            or
            str      r2
            ghi      rb
            or
            lbz      fpmul_dn     ; jump of bb==0
            ghi      r7           ; cc >>= 1
            shr
            phi      r7
            glo      r7
            shrc
            plo      r7
            ghi      r8
            shrc
            phi      r8
            glo      r8
            shrc
            plo      r8
            ghi      ra           ; bb >>= 1
            shr
            phi      ra
            glo      ra
            shrc
            plo      ra
            ghi      rb
            shrc
            phi      rb
            glo      rb
            shrc
            plo      rb
            lbnf     fpmul_lp     ; back to loop if no addition needed
            glo      r8           ; cc += aa
            str      r2
            glo      rd
            add
            plo      r8
            ghi      r8
            str      r2
            ghi      rd
            adc
            phi      r8
            glo      r7
            str      r2
            glo      rc
            adc
            plo      r7
            ghi      r7
            str      r2
            ghi      rc
            adc
            phi      r7
            lbr      fpmul_lp     ; back to beginning of loop
fpmul_dn:   sep      scall        ; assemble answer
            dw       fpnorm
            lbr      fpret_a      ; place result into destination
fpmul_a:    irx                   ; recover destination address
            ldxa
            plo      rf
            ldx
            phi      rf
            glo      rd           ; write a to answer
            str      rf
            inc      rf
            ghi      rd
            str      rf
            inc      rf
            glo      rc
            str      rf
            inc      rf
            ghi      rc
            str      rf
            irx                   ; recover expr stack
            ldxa
            plo      r7
            ldx
            phi      r7
            sep      sret         ; and return to caller

            endp

