#include    macros.inc
#include    bios.inc

            proc     getargs

            lda      r6           ; get passed argument
            str      r2           ; store for add
            glo      r2           ; add stack offset
            add
            plo      rf           ; put into first argument
            ghi      r2           ; high of stack
            adci     0            ; propagate carry
            phi      rf           ; rf now has argument address
            inc      rf           ; remove last call offset
            inc      rf
            lda      r6           ; get passed argument
            str      r2           ; store for add
            glo      r2           ; add stack offset
            add
            plo      rd           ; put into second argument
            ghi      r2           ; high of stack
            adci     0            ; propagate carry
            phi      rd           ; rd now has argument address
            inc      rd           ; remove last call offset
            inc      rd
            sep      sret         ; return to caller

            endp

