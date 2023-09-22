#include    macros.inc
#include    bios.inc

            proc     lte32

            extrn    cmp32
            extrn    false32
            extrn    true32

            sep      scall             ; compare numbers
            dw       cmp32
            lbz      true32            ; true if numbers were equal
            lbdf     true32            ; true if A<B
            lbr      false32           ; otherwise false

            endp

