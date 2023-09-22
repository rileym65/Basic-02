#include    macros.inc
#include    bios.inc

; ******************************************** 
; ***** Floating point division          ***** 
; ***** RF - pointer to first fp number  ***** 
; ***** RD - pointer to second fp number ***** 
; ***** Uses: R7:R8 - answer       (a)   ***** 
; *****       RA:RB - second number (b)  ***** 
; *****       RA    - pointer to (aa)    ***** 
; *****       RB    - pointer to (bb)    ***** 
; *****       R9.0  - exponent           ***** 
; *****       R9.1  - sign               ***** 
; *****       RC:RD - mask               ***** 
; ******************************************** 
            proc    divfpi

            extrn   fpargs
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
            sep      scall        ; get arguments
            dw       fpargs
            glo      r9           ; check for a==0
            lbz      fpret_0      ; return 0 if so
            ghi      r9           ; check for b==0
            lbz      fpret_0      ; return 0 if so
            glo      r9           ; check for a==infinity
            smi      0ffh
            lbz      fpret_a      ; return a if so
            ghi      r9           ; check for b==infinity
            smi      0ffh
            lbz      fpret_b      ; return b if so
            ghi      r9           ; get exp2
            smi      127          ; remove bias
            str      r2           ; store for subtraction
            glo      r9           ; get exp1
            smi      127          ; remove bias
            sm                    ; subtract exp2
            adi      127          ; add bias back in
            plo      r9           ; now have final exp
            ghi      r7           ; get sign of a
            str      r2           ; store for xor
            ghi      ra           ; get sign of b
            xor                   ; now have sign comparison
            shl                   ; shift it into DF
            ldi      0            ; clear D
            shlc                  ; and shift in sign
            phi      r9           ; store sign
            glo      ra           ; put bb on stack
            ori      080h         ; set implied 1 bit
            stxd
            ghi      rb
            stxd
            glo      rb
            stxd
            ldi      0
            stxd
            stxd
            stxd
            glo      r2           ; point RB to bb
            plo      rb
            ghi      r2
            phi      rb
            inc      rb
            glo      r7           ; put aa on stack
            ori      080h         ; set implied 1 bit
            stxd
            ghi      r8
            stxd
            glo      r8
            stxd
            ldi      0
            stxd
            stxd
            stxd
            glo      r2           ; set RA to point to aa
            plo      ra
            ghi      r2
            phi      ra
            inc      ra
            ldi      0            ; clear a
            plo      r8
            phi      r8
            plo      r7
            phi      r7
            plo      rd           ; setup mask
            phi      rd
            phi      rc
            ldi      080h
            plo      rc
fpdiv_lp:   glo      rd           ; need to check for mask==0
            lbnz     fpdiv_1      ; jump if not 0
            ghi      rd
            lbnz     fpdiv_1
            glo      rc
            lbnz     fpdiv_1
            sep      scall        ; division is done, so call normalize
            dw       fpnorm
            glo      r2           ; clear work space from stack
            adi      12
            plo      r2
            ghi      r2
            adci     0
            phi      r2
            lbr      fpret_a      ; and return the answer
fpdiv_1:    smi      0            ; set DF for first byte
            ldi      6            ; 6 bytes to subtract
            plo      re
            sex      rb           ; point x to bb
fpdiv_1a:   lda      ra           ; get byte from aa
            smb                   ; subtract byte from bb from aa
            inc      rb           ; point to next byte
            dec      re           ; decrement count
            glo      re           ; see if done
            lbnz     fpdiv_1a     ; loop back if not
            ldi      6            ; need to move pointers back
            plo      re
fpdiv_1b:   dec      ra
            dec      rb
            dec      re
            glo      re
            lbnz     fpdiv_1b
            lbnf     fpdiv_2      ; jump if b>a
            ldi      6            ; 6 bytes to subtract bb from aa
            plo      re
            smi      0            ; set DF for first subtract
fpdiv_1c:   ldn      ra           ; get byte from a
            smb                   ; subtract bb
            str      ra           ; put it back
            inc      ra           ; increment pointers
            inc      rb
            dec      re           ; decrement byte count
            glo      re           ; see if done
            lbnz     fpdiv_1c     ; loop back if not
            ldi      6            ; need to move pointers back
            plo      re
fpdiv_1d:   dec      ra
            dec      rb
            dec      re
            glo      re
            lbnz     fpdiv_1d
            sex      r2           ; point x back to stack
            glo      rc           ; add mask to answer
            str      r2
            glo      r7
            or
            plo      r7
            ghi      rd
            str      r2
            ghi      r8
            or
            phi      r8
            glo      rd
            str      r2
            glo      r8
            or
            plo      r8
fpdiv_2:    sex      r2           ; point x back to stack
            glo      rc           ; right shift mask
            shr
            plo      rc
            ghi      rd
            shrc
            phi      rd
            glo      rd
            shrc
            plo      rd
            inc      rb           ; need to start at msb of bb
            inc      rb
            inc      rb
            inc      rb
            inc      rb
            inc      rb
            ldi      6            ; 6 bytes in bb to shift right
            plo      re
            adi      0            ; clear DF for first shift
fpdiv_2a:   dec      rb
            ldn      rb           ; get byte from bb
            shrc                  ; shift it right
            str      rb           ; and put it back
            dec      re           ; decrement count
            glo      re           ; see if done
            lbnz     fpdiv_2a     ; loop back if not
            lbr      fpdiv_lp     ; loop for rest of division

            endp

