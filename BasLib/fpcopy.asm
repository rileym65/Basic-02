#include    macros.inc
#include    bios.inc

            proc     fpcopy

            lda      rd           ; copy source to destination
            str      rf
            inc      rf
            lda      rd
            str      rf
            inc      rf
            lda      rd
            str      rf
            inc      rf
            lda      rd
            str      rf
            sep      sret         ; return to caller

            endp

