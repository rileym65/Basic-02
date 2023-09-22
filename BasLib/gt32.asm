#include    macros.inc
#include    bios.inc

            proc     gt32

            extrn    cmp32
            extrn    false32
            extrn    true32

            sep      scall             ; compare numbers
            dw       cmp32
            lbz      false32           ; fails if numbers were equal
            lbnf     true32            ; true if A>B
            lbr      false32           ; otherwise false

            endp

