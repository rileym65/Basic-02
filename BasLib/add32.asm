#include    macros.inc
#include    bios.inc

            proc     add32

            extrn    add32i

            glo      r7                ; setup pointers
            plo      rd
            plo      rf
            ghi      r7                ; setup pointers
            phi      rd
            phi      rf
            inc      rd
            inc      rf
            inc      rf
            inc      rf
            inc      rf
            inc      rf
            sep      scall             ; Perform addition
            dw       add32i
            inc      r7                ; Remove 2nd number from stack
            inc      r7
            inc      r7
            inc      r7
            sep      sret              ; Return to caller

            endp

