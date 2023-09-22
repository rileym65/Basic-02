            proc     fpdata

fpdot1:     db       0cdh, 0cch, 0cch, 03dh
fp_0:       db       00,00,00,00
fp_1:       db       00,00,080h,03fh
fp_2:       db       00,00,000h,040h
fp_10:      db       00,00,020h,041h
fp_100:     db       00,00,0c8h,042h
fp_1000:    db       00,00,07ah,044h
fp_e:       db       054h, 0f8h, 02dh, 040h
fp_pi:      db       0dbh, 00fh, 049h, 040h
fp_3:       db       00,00,040h,040h
fpdot5:     db       000h, 000h, 000h, 03fh
fp_halfpi:  db       0dbh, 00fh, 0c9h, 03fh
fact:       db       000h, 000h, 000h, 000h
            db       000h, 000h, 080h, 03fh
            db       000h, 000h, 000h, 040h
            db       000h, 000h, 0c0h, 040h
            db       000h, 000h, 0c0h, 041h
            db       000h, 000h, 0f0h, 042h
            db       000h, 000h, 034h, 044h
            db       000h, 080h, 09dh, 045h
            db       000h, 080h, 01dh, 047h
            db       000h, 030h, 0b1h, 048h
            db       000h, 07ch, 05dh, 04ah
            db       040h, 045h, 018h, 04ch
            db       0e0h, 067h, 0e4h, 04dh
            db       066h, 094h, 0b9h, 04fh
            db       0d9h, 061h, 0a2h, 051h
            db       0bbh, 03bh, 098h, 053h
            db       0bbh, 03bh, 098h, 055h
            db       077h, 0bfh, 0a1h, 057h
            db       066h, 0f7h, 0b5h, 059h
            db       0c9h, 015h, 0d8h, 05bh
            db       09eh, 00dh, 007h, 05eh
            db       0dfh, 041h, 031h, 060h
            db       093h, 0bah, 073h, 062h
            db       01ah, 02eh, 0afh, 064h
            db       094h, 062h, 003h, 067h
            db       007h, 04ah, 04dh, 069h
            db       026h, 0cch, 0a6h, 06bh
            db       040h, 0bch, 00ch, 06eh
            db       070h, 049h, 076h, 070h
            db       08eh, 032h, 0dfh, 072h
            db       065h, 03fh, 051h, 075h
            db       06ah, 0b5h, 0cah, 077h
            db       06ah, 0b5h, 04ah, 07ah
            db       015h, 00bh, 0d1h, 07ch
            db       0c6h, 01bh, 05eh, 07fh

            public   fpdot1
            public   fp_0
            public   fp_1
            public   fp_2
            public   fp_3
            public   fp_10
            public   fp_100
            public   fp_1000
            public   fpdot5
            public   fp_e
            public   fp_pi
            public   fp_halfpi

            endp

