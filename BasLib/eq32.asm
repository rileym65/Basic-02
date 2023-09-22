#include    macros.inc
#include    bios.inc

            proc     eq32

            extrn    cmp32
            extrn    false32
            extrn    true32

            sep      scall             ; compare numbers
            dw       cmp32
            lbnz     false32           ; fails if numbers were unequal
            lbr      true32            ; true if A=B

            endp

