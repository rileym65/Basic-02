#include    macros.inc
#include    bios.inc

; ********************************************* 
; ***** concatenate string variables      ***** 
; ***** RD - destination string variable  ***** 
; ***** RF - source string variable       ***** 
; ***** uses: RA - Address of source data *****
; *****       RB - Address of dest data   *****
; *****       RC - String length          *****
; ********************************************* 
            proc    concat

            extrn   alloc
            extrn   strlen
            extrn   setstring

            push    rd           ; save destination address
            lda     rf           ; retrieve msb of address
            plo     ra           ; set source address
            ldn     rf           ; get msb of address
            phi     ra
            str     r2           ; save for zero check
            plo     rf           ; store it
            glo     ra           ; recover lsb of address
            phi     rf           ; rf now points to data
            or                   ; check for valid address
            lbz     first0       ; jump if source string is null
            call    strlen       ; get length of string data
            lbr     second       ; jump to second string
first0:     ldi     0            ; clear count
            phi     rc
            plo     rc
second:     pop     rd           ; recover destination variable
            dec     r2           ; keep it on the stack
            dec     r2
            ghi     rc           ; save count
            stxd                 ; save to stack
            glo     rc
            stxd
            lda     rd           ; get addrss of destination data
            plo     rf
            plo     rb
            str     r2           ; store for zero check
            ldn     rd           ; get lsb
            phi     rf           ; rf now points to string data
            phi     rb
            or                   ; check for zero
            lbz     second0      ; jump if null
            call    strlen       ; get length of string
            lbr     cont         ; then continue
second0:    ldi     0            ; set count to 0
            phi     rc
            plo     rc
cont:       irx                  ; add length of source string
            glo     rc           ; lsb of count
            add
            plo     rc
            irx
            ghi     rc
            adc
            phi     rc           ; RC now has total length
            inc     rc           ; 1 byte for terminator
            call    alloc        ; allocate memory for string
            push    rf           ; save this address
            glo     rb           ; check for valid destination data
            str     r2
            ghi     rb
            or
            lbz     donedst      ; jump if no destination data
dstlp:      lda     rb           ; get byte from destination
            lbz     donedst      ; jump if done
            str     rf           ; store into new string
            inc     rf
            lbr     dstlp        ; loop until terminator found
donedst:    glo     ra           ; check source for valid data
            str     r2
            ghi     ra
            or
            lbz     donesrc      ; jump if source is empty
srclp:      lda     ra           ; read byte from source
            lbz     donesrc      ; jump if done copying
            str     rf           ; otherwise write to new string
            inc     rf
            lbr     srclp        ; loop until terminator found
donesrc:    ldi     0            ; write terminator
            str     rf
            pop     rf           ; recover new string data address
            pop     rd           ; recover destination variable
            lbr     setstring    ; and write new string

            endp

