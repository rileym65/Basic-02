#include    macros.inc
#include    bios.inc

            proc    nextvar32

            extrn   next32

            irx            ; move to varAddr
            ldxa           ; keep scall return address
            plo     rd
            ldxa
            phi     rd
            irx
            irx
            glo     rc     ; check for correct address
            sm             ; against stack
            lbnz    nv132  ; jump if not
            irx            ; move to msb
            ghi     rc
            sm             ; compare
            lbnz    nv232  ; jump if not
            dec     r2     ; entry found, move back
            dec     r2
            dec     r2
            dec     r2
            dec     r2
            dec     r2
            lbr     next32
nv132:      irx            ; move past bad entry
nv232:      irx            ; move past bad entry
            irx       
            irx       
            irx       
            irx       
            irx       
            irx       
            irx       
            ghi     rd
            stxd
            glo     rd
            stxd
            lbr     nextvar32

            endp

