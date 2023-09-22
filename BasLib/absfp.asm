#include    macros.inc
#include    bios.inc

            proc     absfp

            inc      r7           ; move to MSB
            inc      r7
            inc      r7
            inc      r7
            ldn      r7           ; retrieve it
            ani      07fh         ; force it positive
            str      r7           ; and put it back
            dec      r7           ; move pointer back
            dec      r7
            dec      r7
            dec      r7
            sep      sret

            endp

