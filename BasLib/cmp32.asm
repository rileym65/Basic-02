#include    macros.inc
#include    bios.inc

            proc     cmp32

            extrn    comp32

            glo      r7                ; copy expr stack to rd
            plo      rd
            plo      rf
            ghi      r7
            phi      rd
            phi      rf
            inc      rd                ; point to lsb of second number
            inc      rf                ; point to lsb of first number
            inc      rf                ; point to lsb of first number
            inc      rf                ; point to lsb of first number
            inc      rf                ; point to lsb of first number
            inc      rf                ; point to lsb of first number
            sep      scall             ; compare numbers
            dw       comp32
            inc      r7                ; Remove numbers from stack
            inc      r7
            inc      r7
            inc      r7
            inc      r7
            inc      r7
            inc      r7
            inc      r7
            sep      sret              ; Return to caller

            endp

