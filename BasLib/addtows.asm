#include    macros.inc
#include    bios.inc

            proc     addtows

            irx                   ; retrieve return address
            ldxa
            phi      r8
            ldx
            plo      r8
            inc      rd           ; move to msb
            inc      rd
            inc      rd
            ldn      rd           ; retrieve
            stxd                  ; and place on stack
            dec      rd
            ldn      rd           ; retrieve next byte
            stxd                  ; and place on stack
            dec      rd
            ldn      rd           ; retrieve next byte
            stxd                  ; and place on stack
            dec      rd
            ldn      rd           ; retrieve next byte
            stxd                  ; and place on stack
            glo      r8           ; put return address back on stack
            stxd
            ghi      r8
            stxd
            sep      sret         ; return to caller

            endp

