#include "header.h"

// R7 - data stack

void library() {
  char ctmp;
  word a;
  word t1,t2,t3,t4;
  ctmp = showCompiler;
  showCompiler = 0;
  Asm("scall:      equ  r4");
  Asm("sret:       equ  r5");
  if (useElfos) {
    output(programStart/256); output(programStart%256);
    output((highest-programStart+1)/256); output((highest-programStart+1)%256);
    output(programStart/256); output(programStart%256);
    }
  if (useElfos || useStg) {
    Asm("init:       lbr  start");
    }
  else {
    Asm("init:       sex  r0");
    Asm("            dis");
    Asm("            db   020h");
    Asm("            ldi  start.1");
    Asm("            phi  r3");
    Asm("            ldi  start.0");
    Asm("            plo  r3");
    }
  lblReturn = address;
  Asm("return:     sep  r3");
  if (passNumber == 1) lblScall = address;
  Asm("call:       plo     re");
  Asm("            ghi     r6");
  Asm("            stxd");
  Asm("            glo     r6");
  Asm("            stxd");
  Asm("            ghi     r3");
  Asm("            phi     r6");
  Asm("            glo     r3");
  Asm("            plo     r6");
  Asm("            lda     r6");
  Asm("            phi     r3");
  Asm("            lda     r6");
  Asm("            plo     r3");
  Asm("            glo     re");
  Asm("            br      call-1");
  Asm("            sep     r3");
  if (passNumber == 1) lblSret = address;
  Asm("ret:        plo     re");
  Asm("            ghi     r6");
  Asm("            phi     r3");
  Asm("            glo     r6");
  Asm("            plo     r3");
  Asm("            irx");
  Asm("            ldxa");
  Asm("            plo     r6");
  Asm("            ldx");
  Asm("            phi     r6");
  Asm("            glo     re");
  Asm("            br      ret-1");

  if (useEf) {
    if (passNumber == 1) lblEf = address;
    Asm("readef:     ldi     0");
    Asm("            bn1     ef1");
    Asm("            ori     1");
    Asm("ef1:        bn2     ef2");
    Asm("            ori     2");
    Asm("ef2:        bn3     ef3");
    Asm("            ori     4");
    Asm("ef3:        bn4     ef4");
    Asm("            ori     8");
    Asm("ef4:        sep     sret");
    }

  if (useSelfTerm) {
    t1 = address;
    Asm("          sep     r3");
    if (passNumber == 1) lblF_delay = address;
    Asm("delay:    ghi     re");
    Asm("          shr");
    Asm("          plo     re");
    Asm("          sex     r2");
    Asm("delay1:   dec     re");
    Asm("          glo     re");
    Asm("          bz      delay-1");
    Asm("          br      delay1");

    if (passNumber == 1) lblF_type = address;
    Asm("f_type:   plo     re");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          glo     re");
    Asm("          phi     rf");
    Asm("          ldi     9");
    Asm("          plo     rf");
    Asm("          ldi     delay.1");
    Asm("          phi     rd");
    Asm("          ldi     delay.0");
    Asm("          plo     rd");
    Asm("          adi     0");
    Asm("sendlp:   bdf     sendnb              ; jump if no bit");
    Asm("          SERSEQ");
    Asm("          br      sendct");
    Asm("sendnb:   SERREQ");
    Asm("          br      sendct");
    Asm("sendct:   sep     rd                  ; perform bit delay");
    Asm("          sex r2");
    Asm("          sex r2");
    Asm("          ghi     rf");
    Asm("          shrc");
    Asm("          phi     rf");
    Asm("          dec     rf");
    Asm("          glo     rf");
    Asm("          bnz     sendlp");
    Asm("          SERREQ");
    Asm("          sep     rd");
    Asm("          sep     rd");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          sep     sret");

    if (passNumber == 1) lblF_read = address;
    Asm("f_read:   ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          ldi     9");
    Asm("          plo     rf");
    Asm("          ldi     delay.1");
    Asm("          phi     rd");
    Asm("          ldi     delay.0");
    Asm("          plo     rd");
    Asm("          ghi     re");
    Asm("          phi     rf");
    Asm("          shr");
    Asm("          shr");
    Asm("          phi     re");
    Asm("          SERP    $");
    Asm("          sep     rd");
    Asm("          ghi     rf");
    Asm("          phi     re");
    Asm("          ghi     rf");
    Asm("          shr");
    Asm("          bdf     recvlpe");
    Asm("recvlp:   ghi     rf");
    Asm("          shr");
    Asm("          SERN    recvlp0");
    Asm("          ori     128");
    Asm("recvlp1:  phi     rf");
    Asm("          sep     rd");
    Asm("          dec     rf");
    Asm("          nop");
    Asm("          nop");
    Asm("          glo     rf");
    Asm("          bnz     recvlp");
    Asm("recvdone: SERREQ");
    Asm("          ghi     rf");
    Asm("          plo     re");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa ");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          glo     re");
    Asm("          sep     sret");
    Asm("recvlp0:  br      recvlp1");
    Asm("recvlpe:  ghi     rf");
    Asm("          shr");
    Asm("          SERN    recvlpe0");
    Asm("          ori     128");
    Asm("          SERREQ");
    Asm("recvlpe1: phi     rf");
    Asm("          sep     rd");
    Asm("          dec     rf");
    Asm("          sex     r2");
    Asm("          sex     r2");
    Asm("          glo     rf");
    Asm("          bnz     recvlpe");
    Asm("          br      recvdone");
    Asm("recvlpe0: SERSEQ");
    Asm("          br      recvlpe1");

    if (passNumber == 1) lblF_setbd = address;
    Asm("f_setbd:  SERREQ");
    Asm("          ldi     0");
    Asm("          phi     rc");
    Asm("          plo     rc");
    Asm("          phi     rb");
    Asm("          plo     rb");
    Asm("timalc_o: SERP    $");
    Asm("end_sb:   SERN    $");
    Asm("          SERP    $");
    Asm("setbd1:   inc     rc");
    Asm("          sex     r2");
    Asm("          sex     r2");
    Asm("          SERN    setbd1");
    Asm("setbd2:   inc     rb");
    Asm("          sex     r2");
    Asm("          sex     r2");
    Asm("          SERP    setbd2");
    Asm("setbd4:   glo     rb");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          shr");
    Asm("          shr");
    Asm("          sm");
    Asm("          lbz     setbd3");
    Asm("          ldi     1");
    Asm("          lskp");
    Asm("setbd3:   ldi     0");
    Asm("          phi     rb");
    Asm("          glo     rc");
    Asm("          smi     4");
    Asm("          phi     re");
    Asm("          ghi     rb");
    Asm("          shr");
    Asm("          ghi     re");
    Asm("          shlc");
    Asm("          phi     re");
    Asm("timalc_rt: sep     sret");

    if (passNumber == 1) lblF_inmsg = address;
    Asm("f_inmsg:  lda     r6");
    Asm("          lbz     return");
    Asm("          sep     scall");
    Asm("          dw      f_type");
    Asm("          lbr     f_inmsg");

    if (passNumber == 1) lblF_msg = address;
    Asm("f_msg:    lda     rf");
    Asm("          lbz     return");
    Asm("          sep     scall");
    Asm("          dw      f_type");
    Asm("          lbr     f_msg");

    if (passNumber == 1) lblF_inmsg = address;
    Asm("f_input:  ldi     0");
    Asm("          plo     ra");
    Asm("inplp:    sep     scall");
    Asm("          dw      f_read");
    Asm("          plo     re");
    Asm("          smi     3");
    Asm("          lbnz    inpgo");
    Asm("inpterm:  smi     0");
    Asm("          ldi     0");
    Asm("          lbr     inpdone2");
    Asm("inpdone:  ldi     0");
    Asm("          shr");
    Asm("inpdone2: str     rf");
    Asm("          sep     sret");
    Asm("inpgo:    smi     5");
    Asm("          lbz     isbs");
    Asm("          smi     5");
    Asm("          lbz     inpdone");
    Asm("          glo     rc");
    Asm("          lbnz    inpcnt");
    Asm("          ghi     rc");
    Asm("          lbnz    inpcnt");
    Asm("          ldi     8");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          lbr     bs2");
    Asm("inpcnt:   glo     re");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          smi     08");
    Asm("          lbnz    nobs");
    Asm("isbs:     glo     ra");
    Asm("          lbz     inplp");
    Asm("          dec     ra");
    Asm("          dec     rf");
    Asm("          inc     rc");
    Asm("bs2:      ldi     32");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          ldi     8");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          lbr     inplp");
    Asm("nobs:     inc     ra");
    Asm("          dec     rc");
    Asm("          lbr     inplp");
    }



  if (useMul || useDiv) {
    if (passNumber == 1) lblMdNorm = address;
    Asm("mdnorm:     ghi     rc");
    Asm("            str     r2");
    Asm("            ghi     rd");
    Asm("            xor");
    Asm("            shl");
    Asm("            ldi     0");
    Asm("            shlc");
    Asm("            plo     re");
    Asm("            ghi     rc");
    Asm("            shl");
    Asm("            lbnf    mdnorm2");
    Asm("            ghi     rc");
    Asm("            xri     0ffh");
    Asm("            phi     rc");
    Asm("            glo     rc");
    Asm("            xri     0ffh");
    Asm("            plo     rc");
    Asm("            inc     rc");
    Asm("mdnorm2:    ghi     rd");
    Asm("            shl");
    Asm("            lbnf    mdnorm3");
    Asm("            ghi     rd");
    Asm("            xri     0ffh");
    Asm("            phi     rd");
    Asm("            glo     rd");
    Asm("            xri     0ffh");
    Asm("            plo     rd");
    Asm("            inc     rd");
    Asm("mdnorm3:    glo     re");
    Asm("            sep     sret");
    }

  if (useMul) {
    if (passNumber == 1) lblMul = address;
    Asm("mul16:    sex     r7");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa");
    Asm("          plo     rc");
    Asm("          ldx");
    Asm("          phi     rc");
    Asm("          sex     r2");
    Asm("          sep     scall");
    Asm("          dw      mdnorm");
    Asm("          plo     re");
    Asm("          ldi     0");
    Asm("          phi     rf");
    Asm("          plo     rf");
    Asm("mulloop:  glo     rd");
    Asm("          lbnz    mulcont");
    Asm("          ghi     rd");
    Asm("          lbnz    mulcont");
    Asm("          glo     re");
    Asm("          shr");
    Asm("          lbnf    mulexit");
    Asm("          glo     rf");
    Asm("          xri     0ffh");
    Asm("          plo     rf");
    Asm("          ghi     rf");
    Asm("          xri     0ffh");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("mulexit:  sex     r7");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          sex     r2");
    Asm("          sep     sret");
    Asm("mulcont:  ghi     rd");
    Asm("          shr");
    Asm("          phi     rd");
    Asm("          glo     rd");
    Asm("          shrc");
    Asm("          plo     rd");
    Asm("          lbnf    mulcont2");
    Asm("          glo     rc");
    Asm("          str     r2");
    Asm("          glo     rf");
    Asm("          add");
    Asm("          plo     rf");
    Asm("          ghi     rc");
    Asm("          str     r2");
    Asm("          ghi     rf");
    Asm("          adc");
    Asm("          phi     rf");
    Asm("mulcont2: glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          lbr     mulloop");
    }

  if (useDiv) {
    if (passNumber == 1) lblDiv = address;
    Asm("div16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            plo     rd");
    Asm("            ldxa");
    Asm("            phi     rd");
    Asm("            ldxa");
    Asm("            plo     rc");
    Asm("            ldx");
    Asm("            phi     rc");
    Asm("            sex     r2");
    Asm("            sep     scall");
    Asm("            dw      mdnorm");
    Asm("            plo     re");
    Asm("            glo     rd");
    Asm("            lbnz    div16_1");
    Asm("            ghi     rd");
    Asm("            lbnz    div16_1");
    Asm("            sex     r7");
    Asm("            ldi     0");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    Asm("div16_1:    ldi     0");
    Asm("            phi     rf");
    Asm("            plo     rf");
    Asm("            phi     r8");
    Asm("            plo     r8");
    Asm("            inc     r8");
    Asm("d16lp1:     ghi     rd");
    Asm("            ani     128");
    Asm("            lbnz    divst");
    Asm("            glo     rd");
    Asm("            shl");
    Asm("            plo     rd");
    Asm("            ghi     rd");
    Asm("            shlc");
    Asm("            phi     rd");
    Asm("            glo     r8");
    Asm("            shl");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            shlc");
    Asm("            phi     r8");
    Asm("            lbr     d16lp1");
    Asm("divst:      glo     rd");
    Asm("            lbnz    divgo");
    Asm("            ghi     rd");
    Asm("            lbnz    divgo");
    Asm("            glo     re");
    Asm("            shr");
    Asm("            lbnf    divret");
    Asm("            ghi     rf");
    Asm("            xri     0ffh");
    Asm("            phi     rf");
    Asm("            glo     rf");
    Asm("            xri     0ffh");
    Asm("            plo     rf");
    Asm("            inc     rf");
    Asm("divret:     sex     r7");
    Asm("            ghi     rf");
    Asm("            stxd");
    Asm("            glo     rf");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    Asm("divgo:      glo     rc");
    Asm("            plo     r9");
    Asm("            ghi     rc");
    Asm("            phi     r9");
    Asm("            glo     rd");
    Asm("            str     r2");
    Asm("            glo     rc");
    Asm("            sm");
    Asm("            plo     rc");
    Asm("            ghi     rd");
    Asm("            str     r2");
    Asm("            ghi     rc");
    Asm("            smb");
    Asm("            phi     rc");
    Asm("            lbdf    divyes");
    Asm("            glo     r9");
    Asm("            plo     rc");
    Asm("            ghi     r9");
    Asm("            phi     rc");
    Asm("            lbr     divno");
    Asm("divyes:     glo     r8");
    Asm("            str     r2");
    Asm("            glo     rf");
    Asm("            add");
    Asm("            plo     rf");
    Asm("            ghi     r8");
    Asm("            str     r2");
    Asm("            ghi     rf");
    Asm("            adc");
    Asm("            phi     rf");
    Asm("divno:      ghi     rd");
    Asm("            shr");
    Asm("            phi     rd");
    Asm("            glo     rd");
    Asm("            shrc");
    Asm("            plo     rd");
    Asm("            ghi     r8");
    Asm("            shr");
    Asm("            phi     r8");
    Asm("            glo     r8");
    Asm("            shrc");
    Asm("            plo     r8");
    Asm("            lbdf    divret");
    Asm("            lbr     divst");
    }

  if (useMod) {
    if (passNumber == 1) lblMod = address;
    Asm("mod16:      sep     scall");
    Asm("            dw      div16");
    Asm("            inc     r7");
    Asm("            inc     r7");
    Asm("            ghi     rc");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            glo     rc");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            sep     sret");
    }

  if (useAdd) {
    if (passNumber == 1) lblAdd = address;
    Asm("add16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            add");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx           ");
    Asm("            adc");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useSub) {
    if (passNumber == 1) lblSub = address;
    Asm("sub16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            sd");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx           ");
    Asm("            sdb");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useAnd) {
    if (passNumber == 1) lblAnd = address;
    Asm("and16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            and");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            and");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useOr) {
    if (passNumber == 1) lblOr = address;
    Asm("or16:       sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            or");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            or");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useXor) {
    if (passNumber == 1) lblXor = address;
    Asm("xor16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            xor");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            xor");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useCmp) {
    if (passNumber == 1) lblTrue = address;
    Asm("true:       ldi     0ffh");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    if (passNumber == 1) lblFalse = address;
    Asm("false:      ldi     000h");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useEq) {
    if (passNumber == 1) lblEq = address;
    Asm("eq16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            lbr     false");
    }

  if (useNe) {
    if (passNumber == 1) lblNe = address;
    Asm("ne16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbnz    true");
    Asm("            lbr     false");
    }

  if (useGt) {
    if (passNumber == 1) lblGt = address;
    Asm("gt16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true");
    Asm("            lbr     false");
    }

  if (useLt) {
    if (passNumber == 1) lblLt = address;
    Asm("lt16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true");
    Asm("            lbr     false");
    }

  if (useGte) {
    if (passNumber == 1) lblGte = address;
    Asm("gte16:      sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true");
    Asm("            lbr     false");
    }

  if (useLte) {
    if (passNumber == 1) lblLte = address;
    Asm("lte16:      sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true");
    Asm("            lbr     false");
    }

  if (useAbs) {
    if (passNumber == 1) lblAbs = address;
    Asm("abs16:    inc     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbnf    absrt");
    Asm("          dec     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adi     1");
    Asm("          str     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adci    0");
    Asm("          str     r7");
    Asm("absrt:    dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useSgn) {
    if (passNumber == 1) lblSgn = address;
    Asm("sgn16:    inc     r7");
    Asm("          lda     r7");
    Asm("          str     r2");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbdf    sgnm");
    Asm("          ldn     r7");
    Asm("          or");
    Asm("          lbz     sgn0");
    Asm("          ldi     0");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ldi     1");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgnm:     ldi     0ffh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgn0:     dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useRnd) {
    if (passNumber == 1) lblRnd = address;
    Asm("rnd16:    ldi     16");
    Asm("          plo     rc");
    Asm("lfsr_lp:  ldi     [LFSR_].1");
    Asm("          phi     r9");
    Asm("          ldi     [LFSR_].0");
    Asm("          plo     r9");
    Asm("          inc     r9");
    Asm("          inc     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          plo     re");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          dec     r9");
    Asm("          dec     r9");
    Asm("          dec     r9");
    Asm("          ldn     r9");
    Asm("          shl");
    Asm("          shlc");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          xri     1");
    Asm("          shr");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          dec     rc");
    Asm("          glo     rc");
    Asm("          lbnz    lfsr_lp");
    Asm("          ldi     [LFSR_].1");
    Asm("          phi     r9");
    Asm("          ldi     [LFSR_].0");
    Asm("          plo     r9");
    Asm("          lda     r9");
    Asm("          plo     rf");
    Asm("          ldn     r9");
    Asm("          phi     rf");
    Asm("          inc     r7");
    Asm("          lda     r7");
    Asm("          plo     r9");
    Asm("          ldn     r7");
    Asm("          phi     r9");
    Asm("          ghi     rf");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     rf");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ghi     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lbr     mod16");
    }

  if (useNext) {
    if (passNumber == 1) lblNextVar = address;
    Asm("nextvar:  irx          ; move to varAddr");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          irx");
    Asm("          irx");
    Asm("          glo     rc   ; check for correct address");
    Asm("          sm           ; against stack");
    Asm("          lbnz    nv1  ; jump if not");
    Asm("          irx          ; move to msb");
    Asm("          ghi     rc");
    Asm("          sm           ; compare");
    Asm("          lbnz    nv2  ; jump if not");
    Asm("          dec     r2   ; entry found, move back");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          lbr     next");
    Asm("nv1:      irx          ; move past bad entry");
    Asm("nv2:      irx          ; move past bad entry");
    Asm("          irx       ");
    Asm("          irx       ");
    Asm("          irx       ");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          lbr     nextvar");
    if (passNumber == 1) lblNext = address;
    Asm("next:     glo     r2");
    Asm("          plo     ra");
    Asm("          ghi     r2");
    Asm("          phi     ra");
    Asm("          sex     ra");
    Asm("          irx          ; return address lsb");
    Asm("          irx          ; return address msb");
    Asm("          irx          ; exec address lsb");
    Asm("          ldxa         ; retrieve exec address");
    Asm("          plo     r9");
    Asm("          ldxa");
    Asm("          phi     r9");
    Asm("          ldxa         ; get it");
    Asm("          plo     rf   ; set rf to address");
    Asm("          ldxa         ; get msb");
    Asm("          phi     rf");
    Asm("          inc     rf   ; point to variable lsb");
    Asm("          ldn     rf   ; retrieve it");
    Asm("          add          ; add in step");
    Asm("          str     rf");
    Asm("          dec     rf   ; point to msb");
    Asm("          irx          ; point to msb of step");
    Asm("          ldn     rf   ; get msb of var value");
    Asm("          adc          ; add in step");
    Asm("          str     rf   ; store back into variable");
    Asm("          irx          ; point to loop count lsb");
    Asm("          ldi     1    ; need to decrement count");
    Asm("          sd           ; decrement it");
    Asm("          str     ra   ; and put it back");
    Asm("          irx          ; point to loop count msb");
    Asm("          ldi     0    ; propagate carry");
    Asm("          sdb");
    Asm("          str     ra   ; and put it back");
    Asm("          sex     r2   ; point X back to R2");
    Asm("          lbdf    stay ; Jump if loop not done");
    Asm("          inc     r2");
    Asm("          dec     ra");
    Asm("          ldxa");
    Asm("          str     ra");
    Asm("          inc     ra");
    Asm("          ldx");
    Asm("          str     ra");
    Asm("          dec     ra");
    Asm("          dec     ra");
    Asm("          glo     ra");
    Asm("          plo     r2");
    Asm("          ghi     ra");
    Asm("          phi     r2");
    Asm("          sep     sret ; nothing to do so return");
    Asm("stay:     glo     r9   ; set return address to exec address");
    Asm("          plo     r6");
    Asm("          ghi     r9");
    Asm("          phi     r6");
    Asm("          sep     sret ; and then return");
    }

  if (useAtoI) {
    /* **************************************** */
    /* ***** Convert ASCII to integer     ***** */
    /* ***** RF - Pointer to ASCII number ***** */
    /* ***** Returns: RC - 16-bit integer ***** */
    /* **************************************** */
    if (passNumber == 1) lblAtoI = address;
    Asm("atoi:     ldi     0");
    Asm("          plo     rc");
    Asm("          phi     rc");
    Asm("atoi_0_1: lda     rf");
    Asm("          plo     re");
    Asm("          smi     '0'");
    Asm("          lbnf    atoi_no");
    Asm("          smi     10");
    Asm("          lbnf    atoi_0_2");
    Asm("atoi_no:  sep     sret");
    Asm("atoi_0_2: glo     re");
    Asm("          smi     '0'");
    Asm("          plo     re");
    Asm("          glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          plo     r8");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          shl");
    Asm("          plo     r8");
    Asm("          ghi     r8");
    Asm("          shlc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          shl");
    Asm("          plo     r8");
    Asm("          ghi     r8");
    Asm("          shlc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          add");
    Asm("          plo     rc");
    Asm("          ghi     r8");
    Asm("          str     r2");
    Asm("          ghi     rc");
    Asm("          adc");
    Asm("          phi     rc");
    Asm("          glo     re");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          add");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          adci    0");
    Asm("          phi     rc");
    Asm("          lbr     atoi_0_1");
    }
  if (useItoA) {
    /* ************************************** */
    /* ***** Convert RC to bcd in M[RF] ***** */
    /* ************************************** */
    if (passNumber == 1) lblToBcd = address;
    Asm("tobcd:    ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp1: ldi     0");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp1");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          ldi     16");
    Asm("          plo     r9");
    Asm("tobcdlp2: ldi     5");
    Asm("          plo     re");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("tobcdlp3: ldn     rf");
    Asm("          smi     5");
    Asm("          lbnf    tobcdlp3a");
    Asm("          adi     8");
    Asm("          str     rf");
    Asm("tobcdlp3a: inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp3");
    Asm("          glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          shlc");
    Asm("          shl");
    Asm("          shl");
    Asm("          shl");
    Asm("          str     rf");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp4: lda     rf");
    Asm("          str     r2");
    Asm("          ldn     rf");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          ldn     r2");
    Asm("          shlc");
    Asm("          ani     0fh");
    Asm("          dec     rf");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp4");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          dec     r9");
    Asm("          glo     r9");
    Asm("          lbnz    tobcdlp2");
    Asm("          sep     sret");

    /* *************************************************** */
    /* ***** Output 16-bit integer                   ***** */
    /* ***** RC - 16-bit integer                     ***** */
    /* ***** RD - Buffer for output                  ***** */
    /* *************************************************** */
    if (passNumber == 1) lblItoA = address;
    Asm("itoa:     glo     r2");
    Asm("          smi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          smbi    0");
    Asm("          phi     r2");
    Asm("          glo     r2");
    Asm("          plo     rf");
    Asm("          ghi     r2");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("          ghi     rc");
    Asm("          shl");
    Asm("          lbnf    itoa1");
    Asm("          ldi     '-'");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("          glo     rc");
    Asm("          xri     0ffh");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          xri     0ffh");
    Asm("          phi     rc");
    Asm("          inc     rc");
    Asm("itoa1:    sep     scall");
    Asm("          dw      tobcd");
    Asm("          glo     r2");
    Asm("          plo     rf");
    Asm("          ghi     r2");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("          ldi     5");
    Asm("          plo     r8");
    Asm("          ldi     4");
    Asm("          phi     r8");
    Asm("itoalp1:  lda     rf");
    Asm("          lbz     itoaz");
    Asm("          str     r2");
    Asm("          ldi     0");
    Asm("          phi     r8");
    Asm("          ldn     r2");
    Asm("itoa2:    adi     030h");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("itoa3:    dec     r8");
    Asm("          glo     r8");
    Asm("          lbnz    itoalp1");
    Asm("          glo     r2");
    Asm("          adi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          adci    0");
    Asm("          phi     r2");
    Asm("          ldi     0");
    Asm("          str     rd");
    Asm("          sep     sret");
    Asm("itoaz:    ghi     r8");
    Asm("          lbz     itoa2");
    Asm("          smi     1");
    Asm("          phi     r8");
    Asm("          lbr     itoa3");
    }


  if (useHeap) {
    /* ******************************************* */
    /* ***** Allocate memory                 ***** */
    /* ***** RC - requested size             ***** */
    /* ***** Returns: RF - Address of memory ***** */
    /* ******************************************* */
    if (passNumber == 1) lblAlloc = address;
    Asm("alloc:     ldi     [HEAP_].0           ; get heap address");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9");
    Asm("           phi     rd");
    Asm("           ldn     r9");
    Asm("           plo     rd");
    Asm("           dec     r9                  ; leave pointer at heap address");
    Asm("alloc_1:   lda     rd                  ; get flags byte");
    Asm("           lbz     alloc_new           ; need new if end of table");
    Asm("           plo     re                  ; save flags");
    Asm("           lda     rd                  ; get block size");
    Asm("           phi     rf");
    Asm("           lda     rd");
    Asm("           plo     rf");
    Asm("           glo     re                  ; is block allocated?");
    Asm("           smi     2");
    Asm("           lbz     alloc_nxt           ; jump if so");
    Asm("           glo     rc                  ; subtract size from block size");
    Asm("           str     r2");
    Asm("           glo     rf");
    Asm("           sm");
    Asm("           plo     rf");
    Asm("           ghi     rc");
    Asm("           str     r2");
    Asm("           ghi     rf");
    Asm("           smb");
    Asm("           phi     rf                  ; RF now has difference");
    Asm("           lbnf    alloc_nxt           ; jumpt if block is too small");
    Asm("           ghi     rf                  ; see if need to split block");
    Asm("           lbnz    alloc_sp            ; jump if so");
    Asm("           glo     rf                  ; get low byte of difference");
    Asm("           ani     0f8h                ; want to see if at least 8 extra bytes");
    Asm("           lbnz    alloc_sp            ; jump if so");
    Asm("alloc_2:   glo     rd                  ; set address for return");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           phi     rf");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           dec     rd");
    Asm("           dec     rd");
    Asm("           ldi     2                   ; mark block as used");
    Asm("           str     rd");
    Asm("           sep     sret                ; and return to caller");
    Asm("alloc_sp:  ghi     rd                  ; save this address");
    Asm("           stxd");
    Asm("           glo     rd");
    Asm("           stxd");
    Asm("           dec     rd                  ; move to lsb of block size");
    Asm("           glo     rc                  ; write requested size");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc                  ; write msb of size");
    Asm("           str     rd");
    Asm("           inc     rd                  ; move back to data");
    Asm("           inc     rd");
    Asm("           glo     rc                  ; now add size");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           add");
    Asm("           plo     rd");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rd                  ; rd now points to new block");
    Asm("           ldi     1                   ; mark as a free block");
    Asm("           str     rd");
    Asm("           inc     rd");
    Asm("           dec     rf                  ; remove 3 bytes from block size");
    Asm("           dec     rf");
    Asm("           dec     rf");
    Asm("           ghi     rf                  ; and write into block header");
    Asm("           str     rd");
    Asm("           inc     rd");
    Asm("           glo     rf");
    Asm("           str     rd");
    Asm("           irx                         ; recover address");
    Asm("           ldxa");
    Asm("           plo     rd");
    Asm("           ldx");
    Asm("           phi     rd");
    Asm("           lbr     alloc_2             ; finish allocating");
    Asm("alloc_nxt: glo     rf                  ; add block size to address");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           add");
    Asm("           plo     rd");
    Asm("           ghi     rf");
    Asm("           str     r2");
    Asm("           ghi     rd");
    Asm("           adc");
    Asm("           phi     rd");
    Asm("           lbr     alloc_1             ; check next cell");
    Asm("alloc_new: lda     r9                  ; retrieve start of heap");
    Asm("           phi     rd");
    Asm("           ldn     r9");
    Asm("           plo     rd");
    Asm("           glo     rc                  ; subtract req. size from pointer");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           sm");
    Asm("           plo     rd");
    Asm("           ghi     rc");
    Asm("           str     r2");
    Asm("           ghi     rd");
    Asm("           smb");
    Asm("           phi     rd");
    Asm("           dec     rd                  ; point to lsb of block size");
    Asm("           glo     rc                  ; write size");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ldi     2                   ; mark as allocated block");
    Asm("           str     rd");
    Asm("           glo     rd                  ; set address");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           phi     rf");
    Asm("           inc     rf                  ; point to actual data space");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           glo     rd                  ; write new heap address");
    Asm("           str     r9");
    Asm("           dec     r9");
    Asm("           ghi     rd");
    Asm("           str     r9");
    Asm("           sep     scall               ; check for out of memory");
    Asm("           dw      checkeom");
    Asm("           sep     sret                ; return to caller");

    /* ************************************** */
    /* ***** Deallocate memory          ***** */
    /* ***** RF - address to deallocate ***** */
    /* ************************************** */
    if (passNumber == 1) lblDealloc = address;
    Asm("dealloc:   dec     rf                  ; move to flags byte");
    Asm("           dec     rf");
    Asm("           dec     rf");
    Asm("           ldi     1                   ; mark block as free");
    Asm("           str     rf");
    Asm("heapgc:    ghi     rc                  ; save consumed registers");
    Asm("           stxd");
    Asm("           glo     rc");
    Asm("           stxd");
    Asm("           ghi     rd");
    Asm("           stxd");
    Asm("           glo     rd");
    Asm("           stxd");
    Asm("           ldi     [HEAP_].0           ; need start of heap");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve heap start address");
    Asm("           phi     rd");
    Asm("           lda     r9");
    Asm("           plo     rd");
    Asm("heapgc_1:  lda     rd                  ; retrieve flags byte");
    Asm("           lbz     heapgc_dn           ; return if end of heap found");
    Asm("           plo     re                  ; save copy of flags");
    Asm("           lda     rd                  ; retrieve block size");
    Asm("           phi     rc");
    Asm("           lda     rd");
    Asm("           plo     rc");
    Asm("           glo     rd                  ; RF=RD+RC, point to next block");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rf");
    Asm("           lda     rf                  ; retrieve flags for next block");
    Asm("           lbz     heapgc_dn           ; return if on last block");
    Asm("           smi     2                   ; is block allocated?");
    Asm("           lbz     heapgc_a            ; jump if so");
    Asm("           glo     re                  ; check flags of current block");
    Asm("           smi     2                   ; is it allocated");
    Asm("           lbz     heapgc_a            ; jump if so");
    Asm("           lda     rf                  ; retrieve next block size into RF");
    Asm("           plo     re");
    Asm("           lda     rf");
    Asm("           plo     rf");
    Asm("           glo     re");
    Asm("           phi     rf");
    Asm("           inc     rf                  ; add 3 bytes for header");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           glo     rf                  ; RC += RF, combine sizes");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rc");
    Asm("           ghi     rf");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rc");
    Asm("           dec     rd                  ; write size of combined blocks");
    Asm("           glo     rc");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc");
    Asm("           str     rd");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           lbr     heapgc_1            ; keep checking for merges");
    Asm("heapgc_a:  glo     rf                  ; move pointer to next block");
    Asm("           plo     rd");
    Asm("           ghi     rf");
    Asm("           phi     rd");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           lbr     heapgc_1            ; and check next block");
    Asm("heapgc_dn: irx                         ; recover consumed registers");
    Asm("           ldxa");
    Asm("           plo     rd");
    Asm("           ldxa");
    Asm("           phi     rd");
    Asm("           ldxa");
    Asm("           plo     rc");
    Asm("           ldx");
    Asm("           phi     rc");
    Asm("           sep     sret                ; return to caller");

    /* ********************************************* */
    /* ***** Return amount of free heap memory ***** */
    /* ***** Returns: RC - free heap memory    ***** */
    /* ********************************************* */
    Asm("hfree:     ldi     0                   ; clear count");
    Asm("           plo     rc");
    Asm("           phi     rc");
    Asm("           ldi     [HEAP_].0           ; setup heap pointer");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve start of heap");
    Asm("           phi     rf");
    Asm("           ldn     r9");
    Asm("           plo     rf");
    Asm("hfree_lp:  lda     rf                  ; get heap allocation status byte");
    Asm("           lbz     hfree_dn            ; jump if end of heap");
    Asm("           plo     re                  ; save this for a moment");
    Asm("           lda     rf                  ; retrieve block size");
    Asm("           phi     rd");
    Asm("           lda     rf");
    Asm("           plo     rd");
    Asm("           str     r2                  ; add size to block address");
    Asm("           glo     rf");
    Asm("           add");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rf");
    Asm("           adc");
    Asm("           phi     rf");
    Asm("           glo     re                  ; recover status byte");
    Asm("           smi     1                   ; is it a free block");
    Asm("           lbnz    hfree_lp            ; jump if not");
    Asm("           glo     rd                  ; add block size to count");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rc");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rc");
    Asm("           lbr     hfree_lp            ; check next block");
    Asm("hfree_dn:  sep     sret                ; and return");

    /* *********************************** */
    /* ***** Check for out of memory ***** */
    /* *********************************** */
    Asm("checkeom:  ghi     rc                  ; save consumed register");
    Asm("           stxd");
    Asm("           glo     rc");
    Asm("           stxd");
    Asm("           ldi     [FREE_].0           ; get end of variable table");
    Asm("           plo     r9");
    Asm("           ldi     [FREE_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve variable table end");
    Asm("           phi     rc");
    Asm("           lda     r9");
    Asm("           plo     rc");
    Asm("           ldi     [HEAP_].0           ; point to heap start");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           inc     r9                  ; point to lsb");
    Asm("           ldn     r9                  ; get heap");
    Asm("           str     r2");
    Asm("           glo     rc                  ; subtract from variable table end");
    Asm("           sm");
    Asm("           dec     r9                  ; point to msb");
    Asm("           ldn     r9                  ; retrieve it");
    Asm("           str     r2");
    Asm("           ghi     rc                  ; subtract from variable table end");
    Asm("           smb");
    Asm("           lbdf    oom                 ; jump of out of memory");
    Asm("           irx                         ; recover consumed register");
    Asm("           ldxa");
    Asm("           plo     rc");
    Asm("           ldx");
    Asm("           phi     rc");
    Asm("           sep     sret                ; and return to caller");
    Asm("oom:       sep     scall               ; display out of memory error");
    Asm("           dw      f_inmsg");
    Asm("           db      'Out of memory: ',0");
    Asm("           lbr     $                   ; show line of error and exit");
    }

  if (useAdd32) {
    /* ************************************************ */
    /* ***** 32-bit Add.    M[RF]=M[RF]+M[RD]     ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("add32i:  sex      rd                ; point x to second number");
    Asm("         ldn      rf                ; get lsb");
    Asm("         add                        ; add second lsb of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 2nd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get second byte");
    Asm("         adc                        ; add second byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 3rd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get third byte");
    Asm("         adc                        ; add third byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to msb");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get msb byte");
    Asm("         adc                        ; add msb byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         sex      r2                ; restore stack");
    Asm("         dec      rf                ; restore registers to original values");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");

    Asm("add32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform addition");
    Asm("         dw       add32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useSub32) {
    /* ************************************************ */
    /* ***** 32-bit subtract.  M[RF]=M[RF]-M[RD]  ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("sub32i:  sex      rd                ; point x to second number");
    Asm("         ldn      rf                ; get lsb");
    Asm("         sm                         ; subtract second lsb of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 2nd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get second byte");
    Asm("         smb                        ; subtract second byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 3rd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get third byte");
    Asm("         smb                        ; subtract third byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to msb");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get msb byte");
    Asm("         smb                        ; subtract msb byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         sex      r2                ; restore stack");
    Asm("         dec      rf                ; restore registers to original values");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");

    Asm("sub32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform subtraction");
    Asm("         dw       sub32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useMul32) {
    /* ************************************************ */
    /* ***** 32-bit multiply. M[RF]=M[RF]*M[RD]   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** In routine:                          ***** */
    /* *****    R9 - points to first number       ***** */
    /* *****    RD - points to second number      ***** */
    /* *****    RF - points to answer             ***** */
    /* ************************************************ */
    Asm("mul32i:  ldi      0                 ; need to zero answer");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         glo      rf                ; r9 will point to first number");
    Asm("         plo      r9");
    Asm("         ghi      rf");
    Asm("         phi      r9");
    Asm("         glo      r2                ; rf will point to where the answer is");
    Asm("         plo      rf");
    Asm("         ghi      r2");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point to LSB of answer");
    Asm("scmul2:  glo      rd                ; need second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; check for zero");
    Asm("         dw       zero32");
    Asm("         lbnf     scmul4            ; jump if number was not zero");
    Asm("         inc      r2                ; now pointing at lsb of answer");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to 2nd byte");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to 3rd byte");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to msb");
    Asm("         ldn      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         sep      sret              ; return to caller");
    Asm("scmul4:  ldn      rd                ; get lsb of second number");
    Asm("         shr                        ; shift low bit into df");
    Asm("         lbnf     scmulno           ; no add needed");
    Asm("         ghi      rd                ; save position of second number");
    Asm("         stxd");
    Asm("         glo      rd");
    Asm("         stxd");
    Asm("         glo      r9                ; rd needs to be first number");
    Asm("         plo      rd");
    Asm("         ghi      r9");
    Asm("         phi      rd");
    Asm("         sep      scall             ; call add routine");
    Asm("         dw       add32i");
    Asm("         irx                        ; recover rd");
    Asm("         ldxa");
    Asm("         plo      rd");
    Asm("         ldx");
    Asm("         phi      rd");
    Asm("scmulno: glo      r9                ; point to first number");
    Asm("         plo      ra");
    Asm("         ghi      r9");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift left");
    Asm("         dw       shl32");
    Asm("         glo      rd                ; now need pointer to second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift right");
    Asm("         dw       shr32");
    Asm("         lbr      scmul2            ; loop until done");

    Asm("mul32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform multiply");
    Asm("         dw       mul32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useDiv32) {
    /* ************************************************ */
    /* ***** 32-bit division. M[RF]=M[RF]/M[RD]   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** In routine:                          ***** */
    /* *****    RF=a                              ***** */
    /* *****    RD=b                              ***** */
    /* *****    RC=result                         ***** */
    /* *****    RB=shift                          ***** */
    /* ************************************************ */
    Asm("div32i:  ldi      0                 ; set sign flag as positive");
    Asm("         str      r2                ; place on the stack");
    Asm("         inc      rf                ; point to msb of first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         ldn      rf                ; retrieve it");
    Asm("         dec      rf                ; restore position");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         ani      080h              ; is number negative");
    Asm("         lbz      div32_1           ; jump if not");
    Asm("         ldi      1                 ; set sign flag");
    Asm("         xor");
    Asm("         stxd                       ; save flag");
    Asm("         glo      rf                ; 2s compliment number");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("         irx                        ; point back to sign flag");
    Asm("div32_1: inc      rd                ; point to msb of second number");
    Asm("         inc      rd");
    Asm("         inc      rd");
    Asm("         ldn      rd                ; retrieve it");
    Asm("         dec      rd                ; restore position");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         ani      080h              ; is number negative");
    Asm("         lbz      div32_2           ; jump if not");
    Asm("         ldi      1                 ; adjust sign flag");
    Asm("         xor");
    Asm("         stxd                       ; save sign flag");
    Asm("         glo      rd                ; 2s compliment second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("         irx");
    Asm("div32_2: dec      r2                ; preserve sign flag");
    Asm("         ldi      0                 ; zero answer on stack");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         glo      r2                ; set RC here");
    Asm("         plo      rc");
    Asm("         ghi      r2");
    Asm("         phi      rc");
    Asm("         inc      rc                ; point rc to lsb of answer");
    Asm("         ldi      1                 ; set shift to 1");
    Asm("         plo      rb");
    Asm("scdiv1:  sep      scall             ; compare a to b");
    Asm("         dw       icomp32");
    Asm("         lbnf     scdiv4            ; jump if b>=a");
    Asm("         glo      rd                ; need to shift b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       shl32");
    Asm("         inc      rb                ; increment shift");
    Asm("         lbr      scdiv1            ; loop until b>=a");
    Asm("scdiv4:  glo      rf                ; point to a");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall             ; is a zero");
    Asm("         dw       zero32");
    Asm("         lbdf     scdivd1           ; jump if it was zero");
    Asm("         glo      rd                ; point to b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; is b zero");
    Asm("         dw       zero32");
    Asm("         lbdf     scdivd1           ; jump if so");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; need to shift result left");
    Asm("         dw       shl32");
    Asm("         sep      scall             ; compare a to b");
    Asm("         dw       comp32");
    Asm("         lbdf     scdiv6            ; jump if a < b");
    Asm("         ldn      rc                ; get LSB of result");
    Asm("         ori      1                 ; set low bit");
    Asm("         str      rc                ; and but it back");
    Asm("         sep      scall             ; subtrcct a from b");
    Asm("         dw       sub32i");
    Asm("scdiv6:  ldn      rd                ; get lsb of b");
    Asm("         shr                        ; see if low bit is set");
    Asm("         lbnf     scdiv5            ; jump if not");
    Asm("         dec      rb                ; mark final shift");
    Asm("         lbr      scdivd1           ; and then done");
    Asm("scdiv5:  glo      rd                ; point to b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; need to shift b right");
    Asm("         dw       shr32");
    Asm("         dec      rb                ; decrement shift");
    Asm("         lbr      scdiv4            ; loop back until done");
    Asm("scdivd1: glo      rb                ; get shift");
    Asm("         shl                        ; shift sign into df");
    Asm("         lbdf     scdivd2           ; jump if so");
    Asm("scdivd3: glo      rb                ; get shift");
    Asm("         lbz      scdivdn           ; jump if zero");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift it left");
    Asm("         dw       shl32");
    Asm("         dec      rb                ; decrement shift");
    Asm("         lbr      scdivd3           ; loop back");
    Asm("scdivd2: glo      rb                ; get shift");
    Asm("         lbz      scdivdn           ; jump if zero");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift it right");
    Asm("         dw       shr32");
    Asm("         inc      rb                ; increment shift");
    Asm("         lbr      scdivd2");
    Asm("scdivdn: ldi      4                 ; 4 bytes to trcnsfer");
    Asm("         plo      r9");
    Asm("scdivd5: lda      rc                ; get result byte");
    Asm("         str      rf                ; store into answer");
    Asm("         inc      rf");
    Asm("         dec      r9                ; decrement count");
    Asm("         glo      r9                ; see if done");
    Asm("         lbnz     scdivd5           ; jump if not");
    Asm("         dec      rf                ; recover answer");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         glo      rc                ; need to clean up the stack");
    Asm("         plo      r2");
    Asm("         ghi      rc");
    Asm("         phi      r2");
    Asm("         ldn      r2                ; retrieve sign");
    Asm("         shr                        ; shift into df");
    Asm("         lbnf     scdivrt           ; jump if signs were the same");
    Asm("         glo      rf                ; otherwise negate number");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("scdivrt: sep      sret              ; return to caller");

    Asm("div32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform division");
    Asm("         dw       div32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useComp32) {
    /* ************************************************ */
    /* ***** 32-bit cmp.  M[RF]-M[RD]             ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** Returns: D=0 if M[RF]=M[RD]          ***** */
    /* *****          DF=1 if M[RF]<M[RD]         ***** */
    /* ************************************************ */
    Asm("comp32:  lda      rd                ; get lsb from second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get lsb from first number");
    Asm("         sm                         ; subtract");
    Asm("         plo      re                ; save as zero test");
    Asm("         lda      rd                ; get 2nd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 2nd byte of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         lda      rd                ; get 3rd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 3rd byte of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         ldn      rd                ; get msb of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         ldn      rf                ; get msb of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         shl                        ; shift sign bit into df");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         dec      rf                ; restore registers");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");
    }

  if (useIComp32) {
    /* ************************************************ */
    /* ***** 32-bit cmp.  M[RD]-M[RF]             ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** Returns: D=0 if M[RD]=M[RF]          ***** */
    /* *****          DF=1 if M[RD]<M[RF]         ***** */
    /* ************************************************ */
    Asm("icomp32: lda      rd                ; get lsb from second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get lsb from first number");
    Asm("         sd                         ; subtract");
    Asm("         plo      re                ; save as zero test");
    Asm("         lda      rd                ; get 2nd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 2nd byte of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         lda      rd                ; get 3rd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 3rd byte of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         ldn      rd                ; get msb of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         ldn      rf                ; get msb of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         shl                        ; shift sign bit into df");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         dec      rf                ; restore registers");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");
    }

  if (useNull32) {
    /* *************************************** */
    /* ***** M[RA] = 0                   ***** */
    /* *************************************** */
    Asm("null32:  ldi      0                 ; need to zero");
    Asm("         str      rA                ; store to lsb");
    Asm("         inc      rA                ; point to second byte");
    Asm("         str      rA                ; store to second byte");
    Asm("         inc      rA                ; point to third byte");
    Asm("         str      rA                ; store to third byte");
    Asm("         inc      rA                ; point to msb");
    Asm("         str      rA                ; store to msb");
    Asm("         dec      rA                ; restore rf");
    Asm("         dec      rA");
    Asm("         dec      rA");
    Asm("         sep      sret              ; return to caller");
    }

  if (useNeg32) {
    /* ********************************************* */
    /* ***** 2s compliment the number in M[RA] ***** */
    /* ********************************************* */
    Asm("neg32:   ldn      ra                ; get lsb");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adi      1                 ; +1");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to 2nd byte");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         inc      ra                ; point to 3rd byte");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         inc      ra                ; point to msb");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sep      sret              ; return");
    }

  if (useShl32) {
    /* ************************************************ */
    /* ***** 32-bit shift left.  M[RA]=M[RA]<<1   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("shl32:   ldn      ra                ; get lsb");
    Asm("         shl                        ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         inc      ra                ; point to second byte");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to third byte");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to msb");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sep      sret              ; and return");
    }

  if (useShr32) {
    /* ************************************************ */
    /* ***** 32-bit shift right. M[RA]=M[RA]>>1   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("shr32:   inc      ra                ; point to msb");
    Asm("         inc      ra");
    Asm("         inc      ra");
    Asm("         ldn      ra                ; get msb");
    Asm("         shr                        ; shift it right");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to third byte");
    Asm("         ldn      ra                ; get third byte");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to second byte");
    Asm("         ldn      ra                ; get second byte");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to lsb");
    Asm("         ldn      ra                ; get lsb");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         sep      sret              ; return to caller");
    }

  if (useZero32) {
/* *************************************** */
/* ***** is zero check               ***** */
/* ***** returnss: DF=1 if M[RA]=0   ***** */
/* *************************************** */
    Asm("zero32:  sex      ra                ; point X to number");
    Asm("         ldxa                       ; get byte 0");
    Asm("         or                         ; combine with byte 1");
    Asm("         irx                        ; point to byte 2");
    Asm("         or                         ; combine");
    Asm("         irx                        ; point to byte 3");
    Asm("         or                         ; combine");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sex      r2                ; X back to 2");
    Asm("         lbnz     notzero           ; jump if not zero");
    Asm("         smi      0                 ; set df");
    Asm("         sep      sret              ; and return");
    Asm("notzero: adi      0                 ; clear df");
    Asm("         sep      sret              ; and return");
    }


  if (useAnd32) {
    /* ************************************************ */
    /* ***** 32-bit And expr stack                ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("and32:   inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useOr32) {
    /* ************************************************ */
    /* ***** 32-bit Or.  expr stack               ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("or32:    inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useXor32) {
    /* ************************************************ */
    /* ***** 32-bit Xor. expr stack               ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("xor32:   inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useCmp32) {
    Asm("true32:     ldi     0ffh");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    Asm("false32:    ldi     000h");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    Asm("cmp32:   glo      r7                ; copy expr stack to rd");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd                ; point to lsb of second number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         sep      scall             ; compare numbers");
    Asm("         dw       comp32");
    Asm("         inc      r7                ; Remove numbers from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useEq32) {
    Asm("eq32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbnz     false32           ; fails if numbers were unequal");
    Asm("         lbr      true32            ; true if A=B");
    }

  if (useNe32) {
    Asm("ne32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbr      true32            ; true if A<>B");
    }

  if (useLt32) {
    Asm("lt32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbdf     true32            ; true if A<B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useGt32) {
    Asm("gt32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbnf     true32            ; true if A>B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useLte32) {
    Asm("lte32:   sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      true32            ; true if numbers were equal");
    Asm("         lbdf     true32            ; true if A<B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useGte32) {
    Asm("gte32:   sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      true32            ; true if numbers were equal");
    Asm("         lbnf     true32            ; true if A>B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useSgn32) {
    Asm("sgn32:    inc     r7");
    Asm("          lda     r7");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbdf    sgnm32");
    Asm("          ldn     r7");
    Asm("          or");
    Asm("          lbz     sgn032");
    Asm("          ldi     0");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ldi     1");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgnm32:   ldi     0ffh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgn032:   dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useItoA32) {
    /* ***************************************** */
    /* ***** Convert RA:RB to bcd in M[RF] ***** */
    /* ***************************************** */
    Asm("tobcd32:     glo     rf           ; transfer address to rc");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     10           ; 10 bytes to clear");
    Asm("             plo     re");
    Asm("tobcd32lp1:  ldi     0");
    Asm("             str     rc           ; store into answer");
    Asm("             inc     rc");
    Asm("             dec     re           ; decrement count");
    Asm("             glo     re           ; get count");
    Asm("             lbnz    tobcd32lp1   ; loop until done");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     32           ; 32 bits to process");
    Asm("             plo     r9");
    Asm("tobcd32lp2:  ldi     10           ; need to process 5 cells");
    Asm("             plo     re           ; put into count");
    Asm("tobcd32lp3:  ldn     rc           ; get byte");
    Asm("             smi     5            ; need to see if 5 or greater");
    Asm("             lbnf    tobcd32lp3a  ; jump if not");
    Asm("             adi     8            ; add 3 to original number");
    Asm("             str     rc           ; and put it back");
    Asm("tobcd32lp3a: inc     rc           ; point to next cell");
    Asm("             dec     re           ; decrement cell count");
    Asm("             glo     re           ; retrieve count");
    Asm("             lbnz    tobcd32lp3   ; loop back if not done");
    Asm("             glo     rb           ; start by shifting number to convert");
    Asm("             shl");
    Asm("             plo     rb");
    Asm("             ghi     rb");
    Asm("             shlc");
    Asm("             phi     rb");
    Asm("             glo     ra");
    Asm("             shlc");
    Asm("             plo     ra");
    Asm("             ghi     ra");
    Asm("             shlc");
    Asm("             phi     ra");
    Asm("             shlc                 ; now shift result to bit 3");
    Asm("             shl");
    Asm("             shl");
    Asm("             shl");
    Asm("             str     rc");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     10           ; 10 cells to process");
    Asm("             plo     re");
    Asm("tobcd32lp4:  lda     rc           ; get current cell");
    Asm("             str     r2           ; save it");
    Asm("             ldn     rc           ; get next cell");
    Asm("             shr                  ; shift bit 3 into df");
    Asm("             shr");
    Asm("             shr");
    Asm("             shr");
    Asm("             ldn     r2           ; recover value for current cell");
    Asm("             shlc                 ; shift with new bit");
    Asm("             ani     0fh          ; keep only bottom 4 bits");
    Asm("             dec     rc           ; point back");
    Asm("             str     rc           ; store value");
    Asm("             inc     rc           ; and move to next cell");
    Asm("             dec     re           ; decrement count");
    Asm("             glo     re           ; see if done");
    Asm("             lbnz    tobcd32lp4   ; jump if not");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             dec     r9           ; decrement bit count");
    Asm("             glo     r9           ; see if done");
    Asm("             lbnz    tobcd32lp2   ; loop until done");
    Asm("             sep     sret         ; return to caller");

    /* *************************************************** */
    /* ***** Convert 32-bit binary to ASCII          ***** */
    /* ***** RF - Pointer to 32-bit integer          ***** */
    /* ***** RD - destination buffer                 ***** */
    /* *************************************************** */
    Asm("itoa32:    lda     rf           ; retrieve number into R7:R8");
    Asm("           plo     rb");
    Asm("           lda     rf");
    Asm("           phi     rb");
    Asm("           lda     rf");
    Asm("           plo     ra");
    Asm("           lda     rf");
    Asm("           phi     ra");
    Asm("           glo     r2           ; make room on stack for buffer");
    Asm("           smi     11");
    Asm("           plo     r2");
    Asm("           ghi     r2");
    Asm("           smbi    0");
    Asm("           phi     r2");
    Asm("           glo     r2           ; RF is output buffer");
    Asm("           plo     rf");
    Asm("           ghi     r2");
    Asm("           phi     rf");
    Asm("           inc     rf");
    Asm("           ghi     ra           ; get high byte");
    Asm("           shl                  ; shift bit to DF");
    Asm("           lbdf    itoa32n      ; negative number");
    Asm("itoa321:   sep     scall        ; convert to bcd");
    Asm("           dw      tobcd32");
    Asm("           glo     r2");
    Asm("           plo     rf");
    Asm("           ghi     r2");
    Asm("           phi     rf");
    Asm("           inc     rf");
    Asm("           ldi     10");
    Asm("           plo     rb");
    Asm("           ldi     9            ; max 9 leading zeros");
    Asm("           phi     rb");
    Asm("loop1:     lda     rf");
    Asm("           lbz     itoa32z      ; check leading zeros");
    Asm("           str     r2           ; save for a moment");
    Asm("           ldi     0            ; signal no more leading zeros");
    Asm("           phi     rb");
    Asm("           ldn     r2           ; recover character");
    Asm("itoa322:   adi     030h");
    Asm("           str     rd           ; store into output buffer");
    Asm("           inc     rd");
    Asm("itoa323:   dec     rb");
    Asm("           glo     rb");
    Asm("           lbnz    loop1");
    Asm("           glo     r2           ; pop work buffer off stack");
    Asm("           adi     11");
    Asm("           plo     r2");
    Asm("           ghi     r2");
    Asm("           adci    0");
    Asm("           phi     r2");
    Asm("           ldi     0            ; place terminator in destination");
    Asm("           str     rd");
    Asm("           sep     sret         ; return to caller");
    Asm("itoa32z:   ghi     rb           ; see if leading have been used up");
    Asm("           lbz     itoa322      ; jump if so");
    Asm("           smi     1            ; decrement count");
    Asm("           phi     rb");
    Asm("           lbr     itoa323      ; and loop for next character");
    Asm("itoa32n:   ldi     '-'          ; show negative");
    Asm("           str     rd           ; write to destination buffer");
    Asm("           inc     rd");
    Asm("           glo     rb           ; 2s compliment");
    Asm("           xri     0ffh");
    Asm("           adi     1");
    Asm("           plo     rb");
    Asm("           ghi     rb");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     rb");
    Asm("           glo     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           plo     ra");
    Asm("           ghi     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     ra");
    Asm("           lbr     itoa321        ; now convert/show number");
    }

  if (useAtoI32) {
    /* **************************************************** */
    /* ***** Convert ascii to int32                   ***** */
    /* ***** RF - buffer to ascii                     ***** */
    /* ***** RD - destinatin int32                    ***** */
    /* ***** Returns R8:R9 result                     ***** */
    /* *****         RF - First non-numeric character ***** */
    /* **************************************************** */
    Asm("atoi32:     ldi     0            ; zero result");
    Asm("            phi     r8");
    Asm("            plo     r8");
    Asm("            phi     r9");
    Asm("            plo     r9");
    Asm("            stxd                 ; store sign on stack");
    Asm("            ldn     rf           ; get byte from input");
    Asm("            smi     '-'          ; check for negative number");
    Asm("            lbnz    atoi32_lp    ; jump if not a negative number");
    Asm("            ldi     1            ; replace sign");
    Asm("            irx");
    Asm("            stxd");
    Asm("            inc     rf           ; move past sign");
    Asm("atoi32_lp:  ldn     rf           ; get byte from input");
    Asm("            smi     '0'          ; see if below digits");
    Asm("            lbnf    atoi32_dn    ; jump if not valid digit");
    Asm("            smi     10           ; check for high of range");
    Asm("            lbdf    atoi32_dn    ; jump if not valid digit");
    Asm("            glo     r9           ; multiply answer by 2");
    Asm("            shl");
    Asm("            plo     r9");
    Asm("            plo     rb           ; put a copy in RA:RB as well");
    Asm("            ghi     r9");
    Asm("            shlc");
    Asm("            phi     r9");
    Asm("            phi     rb");
    Asm("            glo     r8");
    Asm("            shlc");
    Asm("            plo     r8");
    Asm("            plo     ra");
    Asm("            ghi     r8");
    Asm("            shlc");
    Asm("            phi     r8");
    Asm("            phi     ra");
    Asm("            ldi     2            ; want to shift RA:RB twice");
    Asm("            plo     re");
    Asm("atoi32_1:   glo     rb           ; now shift RA:RB");
    Asm("            shl");
    Asm("            plo     rb");
    Asm("            ghi     rb");
    Asm("            shlc");
    Asm("            phi     rb");
    Asm("            glo     ra");
    Asm("            shlc");
    Asm("            plo     ra");
    Asm("            ghi     ra");
    Asm("            shlc");
    Asm("            phi     ra");
    Asm("            dec     re           ; decrement shift count");
    Asm("            glo     re           ; see if done");
    Asm("            lbnz    atoi32_1     ; shift again if not");
    Asm("            glo     rb           ; now add RA:RB to R8:R9");
    Asm("            str     r2");
    Asm("            glo     r9");
    Asm("            add");
    Asm("            plo     r9");
    Asm("            ghi     rb");
    Asm("            str     r2");
    Asm("            ghi     r9");
    Asm("            adc");
    Asm("            phi     r9");
    Asm("            glo     ra");
    Asm("            str     r2");
    Asm("            glo     r8");
    Asm("            adc");
    Asm("            plo     r8");
    Asm("            ghi     ra");
    Asm("            str     r2");
    Asm("            ghi     ra");
    Asm("            str     r2");
    Asm("            ghi     r8");
    Asm("            adc");
    Asm("            phi     r8");
    Asm("            lda     rf           ; get byte from input");
    Asm("            smi     '0'          ; conver to binary");
    Asm("            str     r2           ; and add it to R8:R9");
    Asm("            glo     r9");
    Asm("            add");
    Asm("            plo     r9");
    Asm("            ghi     r9");
    Asm("            adci    0");
    Asm("            phi     r9");
    Asm("            glo     r8");
    Asm("            adci    0");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            adci    0");
    Asm("            phi     r8");
    Asm("            lbr     atoi32_lp    ; loop back for more characters");
    Asm("atoi32_dn:  irx                  ; recover sign");
    Asm("            ldx");
    Asm("            shr                  ; shift into DF");
    Asm("            lbnf    atoi32_dn2   ; jump if not negative");
    Asm("            glo     r9           ; negate the number");
    Asm("            xri     0ffh");
    Asm("            adi     1");
    Asm("            plo     r9");
    Asm("            ghi     r9");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            phi     r9");
    Asm("            glo     r8");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            phi     r8");
    Asm("atoi32_dn2: ghi     r8           ; store result into destination");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            glo     r8");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            ghi     r9");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            glo     r9");
    Asm("            str     rd");
    Asm("            dec     rd           ; restore RD");
    Asm("            dec     rd");
    Asm("            dec     rd");
    Asm("            sep     sret         ; and return to caller");
    }


  if (passNumber == 1) lblStart = address;
  if (useStg) {
    Asm("start:      ghi  r6");
    Asm("            stxd");
    Asm("            glo  r6");
    Asm("            stxd");
    Asm("            ldi  [STG_].1");
    Asm("            phi  rf");
    Asm("            ldi  [STG_].0");
    Asm("            plo  rf");
    Asm("            ghi  r2");
    Asm("            str  rf");
    Asm("            inc  rf");
    Asm("            glo  r2");
    Asm("            str  rf");
    }
  else {
    Asm("start:      ldi  [stack].1");
    Asm("            phi  r2");
    Asm("            ldi  [stack].0");
    Asm("            plo  r2");
    }
  Asm("            ldi  [estack].1");
  Asm("            phi  r7");
  Asm("            ldi  [estack].0");
  Asm("            plo  r7");
  if (useElfos == 0 && useStg == 0) {
    Asm("          ldi  call.1");
    Asm("          phi  r4      ");
    Asm("          ldi  call.0");
    Asm("          plo  r4");
    Asm("          ldi  ret.1");
    Asm("          phi  r5      ");
    Asm("          ldi  ret.0");
    Asm("          plo  r5");
    }
  t1 = variableRAM + (2 * numberOfVariables);
  t2 = getVariable("FREE_");
  Asm("          ldi  [free_].1");
  Asm("          phi  rf");
  Asm("          ldi  [free_].0");
  Asm("          plo  rf");
  if (use32Bits) {
    Asm("          ldi  0");
    Asm("          str  rf");
    Asm("          inc  rf");
    Asm("          str  rf");
    Asm("          inc  rf");
    }
  output(LDI); output(t1/256);                                   //           LDI  freemem.1
  output(STR+RF);                                                //           STR  RF
  output(INC+RF);                                                //           INC  RF
  output(LDI); output(t1%256);                                   //           LDI  freemem.0
  output(STR+RF);                                                //           STR  RF
  if (useData) {
    a = getVariable("DATA_");
    output(LDI); output(a/256); output(PHI+RF);
    output(LDI); output(a%256); output(PLO+RF);
    output(LDI); output(dataAddress/256); output(STR+RF); output(INC+RF);
    output(LDI); output(dataAddress%256); output(STR+RF);
    }
  if (useHeap) {
    a = getVariable("HEAP_");
    output(LDI); output(a/256); output(PHI+RF);
    output(LDI); output(a%256); output(PLO+RF);
    output(LDI); output(heap/256); output(STR+RF); output(INC+RF);
    output(LDI); output(heap%256); output(STR+RF);
    }
  if ((useItoA || useAtoI || useItoA32 || useAtoI32) && useElfos == 0) {
    Asm("          sep  scall");
    Asm("          dw   f_setbd");
    }
  showCompiler = ctmp;
  if (passNumber == 1) runtime = address;
  }

