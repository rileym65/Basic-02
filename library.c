#include "header.h"

// R7 - data stack

void library() {
  char ctmp;
  word a;
  word t1,t2,t3;
  ctmp = showCompiler;
  showCompiler = 0;
  output(SEX+R0);                                                // init:     SEX  R0
  output(DIS); output(0x20);                                     //           DIS  20
  output(LDI); output(lblStart / 256);                           //           LDI  start.1
  output(PHI+R3);                                                //           PHI  R3      
  output(LDI); output(lblStart % 256);                           //           LDI  start.0
  output(PLO+R3);                                                //           PLO  R3
  output(SEP+R3);                                                //           SEP  R3
  lblReturn = address;
  output(SEP+R3);                                                // return:   SEP  R3
  if (passNumber == 1) lblScall = address;
  output(PLO+RE);                                                // scall:    PLO  RE
  output(GHI+R6);                                                //           ghi     r6
  output(STXD);                                                  //           stxd
  output(GLO+R6);                                                //           glo     r6
  output(STXD);                                                  //           stxd
  output(GHI+R3);                                                //           ghi     r3
  output(PHI+R6);                                                //           phi     r6
  output(GLO+R3);                                                //           glo     r3
  output(PLO+R6);                                                //           plo     r6
  output(LDA+R6);                                                //           lda     r6
  output(PHI+R3);                                                //           phi     r3
  output(LDA+R6);                                                //           lda     r6
  output(PLO+R3);                                                //           plo     r3
  output(GLO+RE);                                                //           glo     re
  output(BR); output((lblScall-1)%256);                          //           br      call-1
  output(SEP+R3);                                                //           sep     r3
  if (passNumber == 1) lblSret = address;
  output(PLO+RE);                                                // ret:      plo     re
  output(GHI+R6);                                                //           ghi     r6
  output(PHI+R3);                                                //           phi     r3
  output(GLO+R6);                                                //           glo     r6
  output(PLO+R3);                                                //           plo     r3
  output(IRX);                                                   //           irx
  output(LDXA);                                                  //           ldxa
  output(PLO+R6);                                                //           plo     r6
  output(LDX);                                                   //           ldx
  output(PHI+R6);                                                //           phi     r6
  output(GLO+RE);                                                //           glo     re
  output(BR); output((lblSret-1)%256);                           //           br      ret-1

  if (useEf) {
    if (passNumber == 1) lblEf = address;
    output(LDI); output(0);                                      // readef:   ldi     0
    a = address + 4;
    output(BN1); output(a%256);                                  //           bn1     ef1
    output(ORI); output(1);                                      //           ori     1
    a = address + 4;
    output(BN2); output(a%256);                                  // ef1:      bn2     ef2
    output(ORI); output(2);                                      //           ori     2
    a = address + 4;
    output(BN3); output(a%256);                                  // ef2:      bn3     ef3
    output(ORI); output(4);                                      //           ori     4
    a = address + 4;
    output(BN4); output(a%256);                                  // ef3:      bn4     ef4
    output(ORI); output(8);                                      //           ori     8
    output(SEP+R5);                                              // ef4:      sep     sret
    }

  if (useSelfTerm) {
    t1 = address;
    output(SEP+R3);                                              //           sep     r3
    if (passNumber == 1) lblF_delay = address;
    output(GHI+RE);                                              // delay:    ghi     re
    output(SHR);                                                 //           shr
    output(PLO+RE);                                              //           plo     re
    output(SEX+R2);                                              //           sex     r2
    t2 = address;
    output(DEC+RE);                                              // delay1:   dec     re
    output(GLO+RE);                                              //           glo     re
    output(BZ); output(t1%256);                                  //           bz      delay-1
    output(BR); output(t2%256);                                  //           br      delay1

    if (passNumber == 1) lblF_type = address;
    output(PLO+RE);                                              // type:     plo     re
    output(GHI+RF); output(STXD);                                //           push    rf
    output(GLO+RF); output(STXD);
    output(GHI+RD); output(STXD);                                //           push    rf
    output(GLO+RD); output(STXD);
    output(GLO+RE);                                              //           glo     re
    output(PHI+RF);                                              //           phi     rf
    output(LDI); output(9);                                      //           ldi     9
    output(PLO+RF);                                              //           plo     rf
    output(LDI); output(lblF_delay/256); output(PHI+RD);         //           mov     rd,delay
    output(LDI); output(lblF_delay%256); output(PLO+RD);
    output(ADI); output(0);                                      //           adi     0
    t1 = address;
    a = address + 5;
    output(BDF); output(a%256);                                  // sendlp:   bdf     sendnb              ; jump if no bit
    output(SERSEQ);                                              //           SERSEQ
    a = address + 4;
    output(BR); output(a%256);                                   //           br      sendct
    output(SERREQ);                                              // sendnb:   SERREQ
    a = address + 2;
    output(BR); output(a%256);                                   //           br      sendct
    output(SEP+RD);                                              // sendct:   sep     rd                  ; perform bit delay
    output(SEX+R2);                                              //           sex r2
    output(SEX+R2);                                              //           sex r2
    output(GHI+RF);                                              //           ghi     rf
    output(SHRC);                                                //           shrc
    output(PHI+RF);                                              //           phi     rf
    output(DEC+RF);                                              //           dec     rf
    output(GLO+RF);                                              //           glo     rf
    output(BNZ); output(t1%256);                                 //           bnz     sendlp
    output(SERREQ);                                              //           SERREQ
    output(SEP+RD);                                              //           sep     rd
    output(SEP+RD);                                              //           sep     rd
    output(IRX); output(LDXA); output(PLO+RD);                   //           pop     rd
    output(LDXA); output(PHI+RD);
    output(LDXA); output(PLO+RF);                                //           pop     rf
    output(LDX); output(PHI+RF);
    output(SEP+R5);                                              //           sep     sret

    if (passNumber == 1) lblF_read = address;
    output(GHI+RF); output(STXD);                                // read:     push    rf
    output(GLO+RF); output(STXD);
    output(GHI+RD); output(STXD);                                //           push    rf
    output(GLO+RD); output(STXD);
    output(LDI); output(9);                                      //           ldi     9
    output(PLO+RF);                                              //           plo     rf
    output(LDI); output(lblF_delay/256); output(PHI+RD);         //           mov     rd,delay
    output(LDI); output(lblF_delay%256); output(PLO+RD);
    output(GHI+RE);                                              //           ghi     re
    output(PHI+RF);                                              //           phi     rf
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(PHI+RE);                                              //           phi     re
    a = address;
    output(SERP); output(a%256);                                 //           SERP    $
    output(SEP+RD);                                              //           sep     rd
    output(GHI+RF);                                              //           ghi     rf
    output(PHI+RE);                                              //           phi     re
    output(GHI+RF);                                              //           ghi     rf
    output(SHR);                                                 //           shr
    a = address + 32;
    output(BDF); output(a%256);                                  //           bdf     recvlpe
    t1 = address;
    output(GHI+RF);                                              // recvlp:   ghi     rf
    output(SHR);                                                 //           shr
    a = address + 26;
    output(SERN); output(a%256);                                 //           SERN    recvlp0
    output(ORI); output(128);                                    //           ori     128
    t2 = address;
    output(PHI+RF);                                              // recvlp1:  phi     rf
    output(SEP+RD);                                              //           sep     rd
    output(DEC+RD);                                              //           dec     rf
    output(NOP);                                                 //           nop
    output(NOP);                                                 //           nop
    output(GLO+RF);                                              //           glo     rf
    output(BNZ); output(t1%256);                                 //           bnz     recvlp
    t3 = address;
    output(SERREQ);                                              // recvdone: SERREQ
    output(GHI+RF);                                              //           ghi     rf
    output(PLO+RE);                                              //           plo     re
    output(IRX); output(LDXA); output(PLO+RD);                   //           pop     rd
    output(LDXA); output(PHI+RD);
    output(LDXA); output(PLO+RF);                                //           pop     rf
    output(LDX); output(PHI+RF);
    output(GLO+RE);                                              //           glo     re
    output(SEP+R5);                                              //           sep     sret
    output(BR); output(t2%256);                                  // recvlp0:  br      recvlp1

    t1 = address;
    output(GHI+RF);                                              // recvlpe:  ghi     rf
    output(SHR);                                                 //           shr
    a = address + 15;
    output(SERN); output(a%256);                                 //           SERN    recvlpe0
    output(ORI); output(128);                                    //           ori     128
    output(SERREQ);                                              //           SERREQ
    t2 = address;
    output(PHI+RF);                                              // recvlpe1: phi     rf
    output(SEP+RD);                                              //           sep     rd
    output(DEC+RF);                                              //           dec     rf
    output(SEX+R2);                                              //           sex     r2
    output(SEX+R2);                                              //           sex     r2
    output(GLO+RF);                                              //           glo     rf
    output(BNZ); output(t1%256);                                 //           bnz     recvlpe
    output(BR); output(t3%256);                                  //           br      recvdone
    output(SERSEQ);                                              // recvlpe0: SERSEQ
    output(BR); output(t2%256);                                  //           br      recvlpe1

    if (passNumber == 1) lblF_setbd = address;
    output(SERREQ);                                              // setbaud:  SERREQ
    output(LDI); output(0);                                      //           ldi     0
    output(PHI+RC);                                              //           phi     rc
    output(PLO+RC);                                              //           plo     rc
    output(PHI+RB);                                              //           phi     rb
    output(PLO+RB);                                              //           plo     rb
    a = address;
    output(SERP); output(a%256);                                 // timalc_o: SERP    $
    a = address;
    output(SERN); output(a%256);                                 // end_sb:   SERN    $
    a = address;
    output(SERP); output(a%256);                                 //           SERP    $
    t1 = address;
    output(INC+RC);                                              // setbd1:   inc     rc
    output(SEX+R2);                                              //           sex     r2
    output(SEX+R2);                                              //           sex     r2
    output(SERN); output(t1%256);                                //           SERN    setbd1
    t2 = address;
    output(INC+RB);                                              // setbd2:   inc     rb
    output(SEX+R2);                                              //           sex     r2
    output(SEX+R2);                                              //           sex     r2
    output(SERP); output(t2%256);                                //           SERP    setbd2
    output(GLO+RB);                                              // setbd4:   glo     rb
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(STR+R2);                                              //           str     r2
    output(GLO+RC);                                              //           glo     rc
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(SM);                                                  //           sm
    a = address + 5;
    output(LBZ); output(a/256); output(a%256);                   //           lbz     setbd3
    output(LDI); output(1);                                      //           ldi     1
    output(LSKP);                                                //           lskp
    output(LDI); output(0);                                      // setbd3:   ldi     0
    output(PHI+RB);                                              //           phi     rb
    output(GLO+RC);                                              //           glo     rc
    output(SMI); output(4);                                      //           smi     4
    output(PHI+RE);                                              //           phi     re
    output(GHI+RB);                                              //           ghi     rb
    output(SHR);                                                 //           shr
    output(GHI+RE);                                              //           ghi     re
    output(SHLC);                                                //           shlc
    output(PHI+RE);                                              //           phi     re
    output(SEP+R5);                                              // timalc_rt: sep     sret

    if (passNumber == 1) lblF_inmsg = address;
    output(LDA+R6);                                              // inmsg:    lda     r6
    output(LBZ); output(lblReturn/256); output(lblReturn%256);   //           lbz     return
    output(SEP+R4);                                              //           sep     scall
    output(lblF_type/256); output(lblF_type%256);                //           dw      type
    output(LBR); output(lblF_inmsg/256); output(lblF_inmsg%256); //           lbr     inmsg

    if (passNumber == 1) lblF_msg = address;
    output(LDA+RF);                                              // msg:      lda     rf
    output(LBZ); output(lblReturn/256); output(lblReturn%256);   //           lbz     return
    output(SEP+R4);                                              //           sep     scall
    output(lblF_type/256); output(lblF_type%256);                //           dw      type
    output(LBR); output(lblF_msg/256); output(lblF_msg%256);     //           lbr     msg

    if (passNumber == 1) lblF_inmsg = address;
    output(LDI); output(0);                                      // input:    ldi     0
    output(PLO+RA);                                              //           plo     ra
    t1 = address;
    output(SEP+R4);                                              // inplp:    sep     scall
    output(lblF_read/256); output(lblF_read%256);                //           dw      f_read
    output(PLO+RE);                                              //           plo     re
    output(SMI); output(3);                                      //           smi     3
    a = address + 15;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    inpgo
    output(SMI); output(0);                                      // inpterm:  smi     0
    output(LDI); output(0);                                      //           ldi     0
    a = address + 6;
    output(LBR); output(a/256); output(a%256);                   //           lbr     inpdone2
    t2 = address;
    output(LDI); output(0);                                      // inpdone:  ldi     0
    output(SHR);                                                 //           shr
    output(STR+RF);                                              // inpdone2: str     rf
    output(SEP+R5);                                              //           sep     sret
    output(SMI); output(5);                                      // inpgo:    smi     5
    a = address + 32;
    output(LBZ); output(a/256); output(a%256);                   //           lbz     isbs
    output(SMI); output(5);                                      //           smi     5
    output(LBZ); output(t2/256); output(t2%256);                 //           lbz     inpdone
    output(GLO+RC);                                              //           glo     rc
    a = address + 15;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    inpcnt
    output(GHI+RC);                                              //           ghi     rc
    a = address + 11;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    inpcnt
    output(LDI); output(8);                                      //           ldi     8
    output(SEP+R4);                                              //           sep     scall
    output(lblF_type/256); output(lblF_type%256);                //           dw      f_tty
    a = address + 18;
    output(LBR); output(a/256); output(a%256);                   //           lbr     bs2
    output(GLO+RE);                                              // inpcnt:   glo     re
    output(STR+RF);                                              //           str     rf
    output(INC+RF);                                              //           inc     rf
    output(SMI); output(8);                                      //           smi     08
    a = address + 22;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    nobs
    output(GLO+RA);                                              // isbs:     glo     ra
    output(LBZ); output(t1/256); output(t1%256);                 //           lbz     inplp
    output(DEC+RA);                                              //           dec     ra
    output(DEC+RF);                                              //           dec     rf
    output(INC+RC);                                              //           inc     rc
    output(LDI); output(32);                                     // bs2:      ldi     32
    output(SEP+R4);                                              //           sep     scall
    output(lblF_type/256); output(lblF_type%256);                //           dw      f_tty
    output(LDI); output(8);                                      //           ldi     8
    output(SEP+R4);                                              //           sep     scall
    output(lblF_type/256); output(lblF_type%256);                //           dw      f_tty
    output(LBR); output(t1/256); output(t1%256);                 //           lbr     inplp
    output(INC+RA);                                              // nobs:     inc     ra
    output(DEC+RC);                                              //           dec     rc
    output(LBR); output(t1/256); output(t1%256);                 //           lbr     inplp
    }



  if (useMul || useDiv) {
    if (passNumber == 1) lblMdNorm = address;
    output(GHI+RC);                                              // mdnorm:   ghi     rc
    output(STR+R2);                                              //           str     r2
    output(GHI+RD);                                              //           ghi     rd
    output(XOR);                                                 //           xor
    output(SHL);                                                 //           shl
    output(LDI); output(0x00);                                   //           ldi     0
    output(SHLC);                                                //           shlc
    output(PLO+RE);                                              //           plo     re
    output(GHI+RC);                                              //           ghi     rc
    output(SHL);                                                 //           shl
    a = address;
    output(LBNF); output((a+12)/256); output((a+12)%256);        //           lbnf    mdnorm2
    output(GHI+RC);                                              //           ghi     rc
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PHI+RC);                                              //           phi     rc
    output(GLO+RC);                                              //           glo     rc
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PLO+RC);                                              //           plo     rc
    output(INC+RC);                                              //           inc     rc
    output(GHI+RD);                                              // mdnorm2:  ghi     rd
    output(SHL);                                                 //           shl
    a = address;
    output(LBNF); output((a+12)/256); output((a+12)%256);        //           lbnf    mdnorm3
    output(GHI+RD);                                              //           ghi     rd
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PHI+RD);                                              //           phi     rd
    output(GLO+RD);                                              //           glo     rd
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PLO+RD);                                              //           plo     rd
    output(INC+RD);                                              //           inc     rd
    output(GLO+RE);                                              // mdnorm3:  glo     re
    output(SEP+R5);                                              //           sep     sret
    }
  if (useMul) {
    if (passNumber == 1) lblMul = address;
    output(SEX+R7);                                              // mul15:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(PLO+RD);                                              //           plo     rd
    output(LDXA);                                                //           ldxa
    output(PHI+RD);                                              //           phi     rd
    output(LDXA);                                                //           ldxa
    output(PLO+RC);                                              //           plo     rc
    output(LDX);                                                 //           ldx
    output(PHI+RC);                                              //           phi     rc
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R4);                                              //           sep     scall
    output(lblMdNorm/256); output(lblMdNorm%256);                //           dw      mdnorm
    output(PLO+RE);                                              //           plo     re
    output(LDI); output(0x00);                                   //           ldi     0
    output(PHI+RF);                                              //           phi     rf
    output(PLO+RF);                                              //           plo     rf
    t1 = address;
    output(GLO+RD);                                              // mulloop:  glo     rd
    a = address + 28;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    mulcont
    output(GHI+RD);                                              //           ghi     rd
    a = address + 24;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    mulcont
    output(GLO+RE);                                              //           glo     re
    output(SHR);                                                 //           shr
    a = address + 12;
    output(LBNF); output(a/256); output(a%256);                  //           lbnf    mulexit
    output(GLO+RF);                                              //           glo     rf
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PLO+RF);                                              //           plo     rf
    output(GHI+RF);                                              //           ghi     rf
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PHI+RF);                                              //           phi     rf
    output(INC+RF);                                              //           inc     rf
    output(SEX+R7);                                              // mulexit:  sex     r7
    output(GHI+RF);                                              //           ghi     rf
    output(STXD);                                                //           stxd
    output(GLO+RF);                                              //           glo     rf
    output(STXD);                                                //           stxd
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    output(GHI+RD);                                              // mulcont:  ghi     rd
    output(SHR);                                                 //           shr
    output(PHI+RD);                                              //           phi     rd
    output(GLO+RD);                                              //           glo     rd
    output(SHRC);                                                //           shrc
    output(PLO+RD);                                              //           plo     rd
    a = address + 13;
    output(LBNF); output(a/256); output(a%256);                  //           lbnf    mulcont2
    output(GLO+RC);                                              //           glo     rc
    output(STR+R2);                                              //           str     r2
    output(GLO+RF);                                              //           glo     rf
    output(ADD);                                                 //           add
    output(PLO+RF);                                              //           plo     rf
    output(GHI+RC);                                              //           ghi     rc
    output(STR+R2);                                              //           str     r2
    output(GHI+RF);                                              //           ghi     rf
    output(ADC);                                                 //           adc
    output(PHI+RF);                                              //           phi     rf
    output(GLO+RC);                                              // mulcont2: glo     rc
    output(SHL);                                                 //           shl
    output(PLO+RC);                                              //           plo     rc
    output(GHI+RC);                                              //           ghi     rc
    output(SHLC);                                                //           shlc
    output(PHI+RC);                                              //           phi     rc
    output(LBR); output(t1/256); output(t1%256);                 //           lbr     mulloop
    }
  if (useDiv) {
    if (passNumber == 1) lblDiv = address;
    output(SEX+R7);                                              // div15:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(PLO+RD);                                              //           plo     rd
    output(LDXA);                                                //           ldxa
    output(PHI+RD);                                              //           phi     rd
    output(LDXA);                                                //           ldxa
    output(PLO+RC);                                              //           plo     rc
    output(LDX);                                                 //           ldx
    output(PHI+RC);                                              //           phi     rc
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R4);                                              //           sep     scall
    output(lblMdNorm/256); output(lblMdNorm%256);                //           dw      mdnorm
    output(PLO+RE);                                              //           plo     re
    output(GLO+RD);                                              //           glo     rd
    a = address + 14;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    div16_1
    output(GHI+RD);                                              //           ghi     rd
    a = address + 10;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    div16_1
    output(SEX+R7);                                              //           sex     r7
    output(LDI); output(0x00);                                   //           ldi     0
    output(STXD);                                                //           stxd
    output(STXD);                                                //           stxd
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    output(LDI); output(0x00);                                   // div16_1:  ldi     0
    output(PHI+RF);                                              //           phi     rf
    output(PLO+RF);                                              //           plo     rf
    output(PHI+R8);                                              //           phi     r8
    output(PLO+R8);                                              //           plo     r8
    output(INC+R8);                                              //           inc     r8
    t1 = address;
    output(GHI+RD);                                              // d16lp1:   ghi     rd
    output(ANI); output(128);                                    //           ani     128
    a = address + 18;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    divst
    output(GLO+RD);                                              //           glo     rd
    output(SHL);                                                 //           shl
    output(PLO+RD);                                              //           plo     rd
    output(GHI+RD);                                              //           ghi     rd
    output(SHLC);                                                //           shlc
    output(PHI+RD);                                              //           phi     rd
    output(GLO+R8);                                              //           glo     r8
    output(SHL);                                                 //           shl
    output(PLO+R8);                                              //           plo     r8
    output(GHI+R8);                                              //           ghi     r8
    output(SHLC);                                                //           shlc
    output(PHI+R8);                                              //           phi     r8
    output(LBR); output(t1/256); output(t1%256);                 //           lbr     d16lp1
    t2 = address;
    output(GLO+RD);                                              // divst:    glo     rd
    a = address + 28;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    divgo
    output(GHI+RD);                                              //           ghi     rd
    a = address + 24;
    output(LBNZ); output(a/256); output(a%256);                  //           lbnz    divgo
    output(GLO+RE);                                              //           glo     re
    output(SHR);                                                 //           shr
    a = address + 12;
    output(LBNF); output(a/256); output(a%256);                  //           lbnf    divret
    output(GHI+RF);                                              //           ghi     rf
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PHI+RF);                                              //           phi     rf
    output(GLO+RF);                                              //           glo     rf
    output(XRI); output(0xff);                                   //           xri     0ffh
    output(PLO+RF);                                              //           plo     rf
    output(INC+RF);                                              //           inc     rf
    output(SEX+R7);                                              // divret:   sex     r7
    output(GHI+RF);                                              //           ghi     rf
    output(STXD);                                                //           stxd
    output(GLO+RF);                                              //           glo     rf
    output(STXD);                                                //           stxd
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    output(GLO+RC);                                              // divgo:    glo     rc
    output(PLO+R9);                                              //           plo     r9
    output(GHI+RC);                                              //           ghi     rc
    output(PHI+R9);                                              //           phi     r9
    output(GLO+RD);                                              //           glo     rd
    output(STR+R2);                                              //           str     r2
    output(GLO+RC);                                              //           glo     rc
    output(SM);                                                  //           sm
    output(PLO+RC);                                              //           plo     rc
    output(GHI+RD);                                              //           ghi     rd
    output(STR+R2);                                              //           str     r2
    output(GHI+RC);                                              //           ghi     rc
    output(SMB);                                                 //           smb
    output(PHI+RC);                                              //           phi     rc
    a = address + 10;
    output(LBDF); output(a/256); output(a%256);                  //           lbdf    divyes
    output(GLO+R9);                                              //           glo     r9
    output(PLO+RC);                                              //           plo     rc
    output(GHI+R9);                                              //           ghi     r9
    output(PHI+RC);                                              //           phi     rc
    a = address + 13;
    output(LBR); output(a/256); output(a%256);                   //           lbr     divno
    output(GLO+R8);                                              // divyes:   glo     r8
    output(STR+R2);                                              //           str     r2
    output(GLO+RF);                                              //           glo     rf
    output(ADD);                                                 //           add
    output(PLO+RF);                                              //           plo     rf
    output(GHI+R8);                                              //           ghi     r8
    output(STR+R2);                                              //           str     r2
    output(GHI+RF);                                              //           ghi     rf
    output(ADC);                                                 //           adc
    output(PHI+RF);                                              //           phi     rf
    output(GHI+RD);                                              //divno:     ghi     rd
    output(SHR);                                                 //           shr
    output(PHI+RD);                                              //           phi     rd
    output(GLO+RD);                                              //           glo     rd
    output(SHRC);                                                //           shrc
    output(PLO+RD);                                              //           plo     rd
    output(GHI+R8);                                              //           ghi     r8
    output(SHR);                                                 //           shr
    output(PHI+R8);                                              //           phi     r8
    output(GLO+R8);                                              //           glo     r8
    output(SHRC);                                                //           shrc
    output(PLO+R8);                                              //           plo     r8
    output(LBR); output(t2/256); output(t2%256);                 //           lbr     divst
    }

  if (useAdd) {
    if (passNumber == 1) lblAdd = address;
    output(SEX+R7);                                              // add16:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx
    output(ADD);                                                 //           add
    output(STXD);                                                //           stxd
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx           
    output(ADC);                                                 //           adc
    output(STXD);                                                //           stxd
    output(DEC+R7);                                              //           dec     r2
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useSub) {
    if (passNumber == 1) lblSub = address;
    output(SEX+R7);                                              // sub16:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx
    output(SD);                                                  //           sd
    output(STXD);                                                //           stxd
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx           
    output(SDB);                                                 //           sdb
    output(STXD);                                                //           stxd
    output(DEC+R7);                                              //           dec     r2
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useAnd) {
    if (passNumber == 1) lblAnd = address;
    output(SEX+R7);                                              // and16:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx
    output(AND);                                                 //           and
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(LDXA);                                                //           ldxa
    output(INC+R7);                                              //           inc     r2
    output(AND);                                                 //           and
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(DEC+R7);                                              //           dec     r2
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useOr) {
    if (passNumber == 1) lblOr = address;
    output(SEX+R7);                                              // or16:     sex     r7
    output(IRX);                                                 // or16:     irx
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx
    output(OR);                                                  //           or
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(LDXA);                                                //           ldxa
    output(INC+R7);                                              //           inc     r2
    output(OR);                                                  //           or
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(DEC+R7);                                              //           dec     r2
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useXor) {
    if (passNumber == 1) lblXor = address;
    output(SEX+R7);                                              // xor16:    sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(IRX);                                                 //           irx
    output(XOR);                                                 //           xor
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(LDXA);                                                //           ldxa
    output(INC+R7);                                              //           inc     r2
    output(XOR);                                                 //           xor
    output(STR+R7);                                              //           str     r2
    output(DEC+R7);                                              //           dec     r2
    output(DEC+R7);                                              //           dec     r2
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useCmp) {
    if (passNumber == 1) lblTrue = address;
    output(LDI); output(0xff);                                   // true;     ldi     0ffh
    output(SEX+R7);                                              //           sex     r7
    output(STXD);                                                //           stxd
    output(STXD);                                                //           stxd
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret

    if (passNumber == 1) lblFalse = address;
    output(LDI); output(0x00);                                   // false:    ldi     000h
    output(SEX+R7);                                              //           sex     r7
    output(STXD);                                                //           stxd
    output(STXD);                                                //           stxd
    output(SEX+R2);                                              //           sex     r2
    output(SEP+R5);                                              //           sep     sret
    }

  if (useEq) {
    if (passNumber == 1) lblEq = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // eq16:     call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBZ); output(lblTrue/256); output(lblTrue%256);       //           lbz     true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useNe) {
    if (passNumber == 1) lblNe = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // ne16:     call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBNZ); output(lblTrue/256); output(lblTrue%256);      //           lbnz    true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useGt) {
    if (passNumber == 1) lblGt = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // gt16:     call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBZ); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    output(LDN+R7);                                              //           ldn     r7
    output(SHL);                                                 //           shl
    output(LBNF); output(lblTrue/256); output(lblTrue%256);      //           lbnf    true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useLt) {
    if (passNumber == 1) lblLt = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // lt16:     call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBZ); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    output(LDN+R7);                                              //           ldn     r7
    output(SHL);                                                 //           shl
    output(LBDF); output(lblTrue/256); output(lblTrue%256);      //           lbdf    true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useGte) {
    if (passNumber == 1) lblGte = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // gte16:    call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBZ); output(lblTrue/256); output(lblTrue%256);       //           lbz     true
    output(LDN+R7);                                              //           ldn     r7
    output(SHL);                                                 //           shl
    output(LBNF); output(lblTrue/256); output(lblTrue%256);      //           lbnf    true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useLte) {
    if (passNumber == 1) lblLte = address;
    output(SEP+R4); output(lblSub/256); output(lblSub%256);      // lte16:    call    sub16
    output(SEX+R7);                                              //           sex     r7
    output(IRX);                                                 //           irx
    output(LDXA);                                                //           ldxa
    output(OR);                                                  //           or
    output(SEX+R2);                                              //           sex     r2
    output(LBZ); output(lblTrue/256); output(lblTrue%256);       //           lbz     true
    output(LDN+R7);                                              //           ldn     r7
    output(SHL);                                                 //           shl
    output(LBDF); output(lblTrue/256); output(lblTrue%256);      //           lbdf    true
    output(LBR); output(lblFalse/256); output(lblFalse%256);     //           lbz     false
    }

  if (useAtoI) {
    /* **************************************** */
    /* ***** Convert ASCII to integer     ***** */
    /* ***** RF - Pointer to ASCII number ***** */
    /* ***** Returns: RC - 16-bit integer ***** */
    /* **************************************** */
    if (passNumber == 1) lblAtoI = address;
    output(LBR); output(t2/256); output(t2%256);                 //           lbr     divst
    output(LDI); output(0x00);                                   // atoi:     ldi     0
    output(PLO+RC);                                              //           plo     rc
    output(PHI+RC);                                              //           phi     rc
    t1 = address;
    output(LDA+RF);                                              // atoi_0_1: lda     rf
    output(PLO+RE);                                              //           plo     re
    output(SMI); output('0');                                    //           smi     '0'
    a = address + 8;
    output(LBNF); output(a/256); output(a%256);            //           lbnf    atoi_no
    output(SMI); output(10);                                     //           smi     10
    a = address + 1;
    output(LBNF); output(a/256); output(a%256);            //           lbnf    atoi_0_2
    output(SEP+R5);                                              // atoi_no:  sep     sret
    output(GLO+RE);                                              // atoi_0_2: glo     re
    output(SMI); output('0');                                    //           smi     '0'
    output(PLO+RE);                                              //           plo     re
    output(GLO+RC);                                              //           glo     rc
    output(SHL);                                                 //           shl
    output(PLO+RC);                                              //           plo     rc
    output(PLO+R8);                                              //           plo     r8
    output(GHI+RC);                                              //           ghi     rc
    output(SHLC);                                                //           shlc
    output(PHI+RC);                                              //           phi     rc
    output(PHI+R8);                                              //           phi     r8
    output(GLO+R8);                                              //           glo     r8
    output(SHL);                                                 //           shl
    output(PLO+R8);                                              //           plo     r8
    output(GHI+R8);                                              //           ghi     r8
    output(SHLC);                                                //           shlc
    output(PHI+R8);                                              //           phi     r8
    output(GLO+R8);                                              //           glo     r8
    output(SHL);                                                 //           shl
    output(PLO+R8);                                              //           plo     r8
    output(GHI+R8);                                              //           ghi     r8
    output(SHLC);                                                //           shlc
    output(PHI+R8);                                              //           phi     r8
    output(GLO+R8);                                              //           glo     r8
    output(STR+R2);                                              //           str     r2
    output(GLO+RC);                                              //           glo     rc
    output(ADD);                                                 //           add
    output(PLO+RC);                                              //           plo     rc
    output(GHI+R8);                                              //           ghi     r8
    output(STR+R2);                                              //           str     r2
    output(GHI+RC);                                              //           ghi     rc
    output(ADC);                                                 //           adc
    output(PHI+RC);                                              //           phi     rc
    output(GLO+RE);                                              //           glo     re
    output(STR+R2);                                              //           str     r2
    output(GLO+RC);                                              //           glo     rc
    output(ADD);                                                 //           add
    output(PLO+RC);                                              //           plo     rc
    output(GHI+RC);                                              //           ghi     rc
    output(ADCI); output(0);                                     //           adci    0
    output(PHI+RC);                                              //           phi     rc
    output(LBR); output(t1/256); output(t1%256);                 //           lbr     atoi_0_1
    }
  if (useItoA) {
    /* ************************************** */
    /* ***** Convert RC to bcd in M[RD] ***** */
    /* ************************************** */
    if (passNumber == 1) lblToBcd = address;
    output(GHI+RD); output(STXD);                                // tobcd:    push    rd
    output(GLO+RD); output(STXD);
    output(LDI); output(5);                                      //           ldi     5
    output(PLO+RE);                                              //           plo     re
    t1 = address;
    output(LDI); output(0);                                      // tobcdlp1: ldi     0
    output(STR+RD);                                              //           str     rd
    output(INC+RD);                                              //           inc     rd
    output(DEC+RE);                                              //           dec     re
    output(GLO+RE);                                              //           glo     re
    output(LBNZ); output(t1/256); output(t1%256);                //           lbnz    tobcdlp1
    output(IRX); output(LDXA); output(PLO+RD);                   //           pop     rd
    output(LDX); output(PHI+RD);
    output(LDI); output(16);                                     //           ldi     16
    output(PLO+R9);                                              //           plo     r9
    t1 = address;
    output(LDI); output(5);                                      // tobcdlp2: ldi     5
    output(PLO+RE);                                              //           plo     re
    output(GHI+RD); output(STXD);                                //           push    rd
    output(GLO+RD); output(STXD);
    t2 = address;
    output(LDN+RD);                                              // tobcdlp3: ldn     rd
    output(SMI); output(5);                                      //           smi     5
    a = address + 6;
    output(LBNF); output(a/256); output(a%256);                  //           lbnf    tobcdlp3a
    output(ADI); output(8);                                      //           adi     8
    output(STR+RD);                                              //           str     rd
    output(INC+RD);                                              // tobcdlp3a: inc     rd
    output(DEC+RE);                                              //           dec     re
    output(GLO+RE);                                              //           glo     re
    output(LBNZ); output(t2/256); output(t2%256);                //           lbnz    tobcdlp3
    output(GLO+RC);                                              //           glo     rc
    output(SHL);                                                 //           shl
    output(PLO+RC);                                              //           plo     rc
    output(GHI+RC);                                              //           ghi     rc
    output(SHLC);                                                //           shlc
    output(PHI+RC);                                              //           phi     rc
    output(SHLC);                                                //           shlc
    output(SHL);                                                 //           shl
    output(SHL);                                                 //           shl
    output(SHL);                                                 //           shl
    output(STR+RD);                                              //           str     rd
    output(IRX); output(LDXA); output(PLO+RD);                   //           pop     rd
    output(LDX); output(PHI+RD);
    output(GHI+RD); output(STXD);                                //           push    rd
    output(GLO+RD); output(STXD);
    output(LDI); output(5);                                      //           ldi     5
    output(PLO+RE);                                              //           plo     re
    t3 = address;
    output(LDA+RD);                                              // tobcdlp4: lda     rd
    output(STR+R2);                                              //           str     r2
    output(LDN+RD);                                              //           ldn     rd
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(SHR);                                                 //           shr
    output(LDN+R2);                                              //           ldn     r2
    output(SHLC);                                                //           shlc
    output(ANI); output(0x0f);                                   //           ani     0fh
    output(DEC+RD);                                              //           dec     rd
    output(STR+RD);                                              //           str     rd
    output(INC+RD);                                              //           inc     rd
    output(DEC+RE);                                              //           dec     re
    output(GLO+RE);                                              //           glo     re
    output(LBNZ); output(t3/256); output(t3%256);                //           lbnz    tobcdlp
    output(IRX); output(LDXA); output(PLO+RD);                   //           pop     rd
    output(LDX); output(PHI+RD);
    output(DEC+R9);                                              //           dec     r9
    output(GLO+R9);                                              //           glo     r9
    output(LBNZ); output(t1/256); output(t1%256);                //           lbnz    tobcdlp2
    output(SEP+R5);                                              //           sep     sret
    /* *************************************************** */
    /* ***** Output 16-bit integer                   ***** */
    /* ***** RC - 16-bit integer                     ***** */
    /* *************************************************** */
    if (passNumber == 1) lblItoA = address;
    output(GLO+R2);                                               // itoa:     glo     r2
    output(SMI); output(6);                                       //           smi     6
    output(PLO+R2);                                               //           plo     r2
    output(GHI+R2);                                               //           ghi     r2
    output(SMBI); output(0);                                      //           smbi    0
    output(PHI+R2);                                               //           phi     r2
    output(GLO+R2); output(PLO+RD);                               //           mov     rd,r2
    output(GHI+R2); output(PHI+RD);
    output(INC+RD);                                               //           inc     rd
    output(GHI+RC);                                               //           ghi     rc
    output(SHL);                                                  //           shl
    a = address  + 17;
    output(LBNF); output(a/256); output(a%256);                   //           lbnf    itoa1
    output(LDI); output('-');                                     //           ldi     '-'
    output(SEP+R4); output(lblF_type/256); output(lblF_type%256); //           sep     scall f_type
    output(GLO+RC);                                               //           glo     rc
    output(XRI); output(0xff);                                    //           xri     0ffh
    output(PLO+RC);                                               //           plo     rc
    output(GHI+RC);                                               //           ghi     rc
    output(XRI); output(0xff);                                    //           xri     0ffh
    output(PHI+RC);                                               //           phi     rc
    output(INC+RC);                                               //           inc     rc
    output(SEP+R4); output(lblToBcd/256); output(lblToBcd%256);   // itoa1:    sep     scall        ; convert to bcd
    output(GLO+R2); output(PLO+RD);                               //           mov     rd,r2
    output(GHI+R2); output(PHI+RD);
    output(INC+RD);                                               //           inc     rd
    output(LDI); output(5);                                       //           ldi     5
    output(PLO+R8);                                               //           plo     r8
    output(LDI); output(4);                                       //           ldi     4
    output(PHI+R8);                                               //           phi     r8
    t1 = address;
    output(LDA+RD);                                               // itoalp1:  lda     rd
    a = address + 27;
    output(LBZ); output(a/256); output(a%256);                    //           lbz     itoaz
    output(STR+R2);                                               //           str     r2
    output(LDI); output(0);                                       //           ldi     0
    output(PHI+R8);                                               //           phi     r8
    output(LDN+R2);                                               //           ldn     r2
    t2 = address;
    output(ADI); output(0x30);                                    // itoa2:    adi     030h
    output(SEP+R4); output(lblF_type/256); output(lblF_type%256); //           sep     scall f_type
    t3 = address;
    output(DEC+R8);                                               // itoa3:    dec     r8
    output(GLO+R8);                                               //           glo     r8
    output(LBNZ); output(t1/256); output(t1%256);                 //           lbnz    itoalp1
    output(GLO+R2);                                               //           glo     r2
    output(ADI); output(6);                                       //           adi     6
    output(PLO+R2);                                               //           plo     r2
    output(GHI+R2);                                               //           ghi     r2
    output(ADCI); output(0);                                      //           adci    0
    output(PHI+R2);                                               //           phi     r2
    output(SEP+R5);                                               //           sep     sret
    output(GHI+R8);                                               // itoaz:    ghi     r8
    output(LBZ); output(t2/256); output(t2%256);                  //           lbz     itoa2
    output(SMI); output(1);                                       //           smi     1
    output(PHI+R8);                                               //           phi     r8
    output(LBR); output(t3/256); output(t3%256);                  //           lbr     itoa3
    }
  if (passNumber == 1) lblStart = address;
  output(LDI); output(stack / 256);                              //           LDI  stack.1
  output(PHI+R2);                                                //           PHI  R2      
  output(LDI); output(stack % 256);                              //           LDI  stack.0
  output(PLO+R2);                                                //           PLO  R2
  output(LDI); output(estack / 256);                             //           LDI  estack.1
  output(PHI+R7);                                                //           PHI  R7      
  output(LDI); output(estack % 256);                             //           LDI  estack.0
  output(PLO+R7);                                                //           PLO  R7
  output(LDI); output(lblScall / 256);                           //           LDI  scall.1
  output(PHI+R4);                                                //           PHI  R4      
  output(LDI); output(lblScall % 256);                           //           LDI  scall.0
  output(PLO+R4);                                                //           PLO  R4
  output(LDI); output(lblSret / 256);                            //           LDI  sret.1
  output(PHI+R5);                                                //           PHI  R5      
  output(LDI); output(lblSret % 256);                            //           LDI  sret.0
  output(PLO+R5);                                                //           PLO  R5
  if (useItoA || useAtoI) {
    output(SEP+R4);                                              //           SEP  SCALL
    output(lblF_setbd/256); output(lblF_setbd%256);              //           DW   F_SETBD
    }
  showCompiler = ctmp;
  }

