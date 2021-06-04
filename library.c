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
    Asm(" readef:    ldi     0");
    Asm("            bn1     ef1");
    Asm("            ori     1");
    Asm(" ef1:       bn2     ef2");
    Asm("            ori     2");
    Asm(" ef2:       bn3     ef3");
    Asm("            ori     4");
    Asm(" ef3:       bn4     ef4");
    Asm("            ori     8");
    Asm(" ef4:       sep     sret");
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
    Asm("            lbz     false");
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
    Asm("            lbz     false");
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
    Asm("            lbz     false");
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
    Asm("            lbz     false");
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
    Asm("            lbz     false");
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
    Asm("            lbz     false");
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
    Asm("          irx          ; move past call return");
    Asm("          irx          ; need a copy of return addr");
    Asm("          irx          ; need a copy of return addr");
    Asm("          irx          ; exec msb");
    Asm("          irx          ; var addr lsb");
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
    Asm("          lda     rf   ; retrieve variable value");
    Asm("          str     r7   ; store on expr stack");
    Asm("          dec     r7");
    Asm("          ldn     rf");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          irx          ; retrieve loop end value");
    Asm("          ldxa");
    Asm("          plo     re");
    Asm("          ldx");
    Asm("          str     r7");
    Asm("          dec     r7   ; exp stack ready ");
    Asm("          glo     re");
    Asm("          str     r7");
    Asm("          dec     r7   ; exp stack ready ");
    Asm("          sex     r2");
    Asm("          sep     scall");
    Asm("          dw      sub16");
    Asm("          inc     r7   ; point to msb");
    Asm("          inc     r7");
    Asm("          ldn     r7   ; get it");
    Asm("          shl          ; was it negative");
    Asm("          lbdf    stay");
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
    Asm("stay:     inc     r2   ; move back");
    Asm("          inc     r2");
    Asm("          inc     r2");
    Asm("          ldxa");
    Asm("          plo     r6");
    Asm("          ldx");
    Asm("          phi     r6   ; into r6");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          sep     sret  ; return");
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
    /* ***** Convert RC to bcd in M[RD] ***** */
    /* ************************************** */
    if (passNumber == 1) lblToBcd = address;
    Asm("tobcd:    ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp1: ldi     0");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp1");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldx");
    Asm("          phi     rd");
    Asm("          ldi     16");
    Asm("          plo     r9");
    Asm("tobcdlp2: ldi     5");
    Asm("          plo     re");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("tobcdlp3: ldn     rd");
    Asm("          smi     5");
    Asm("          lbnf    tobcdlp3a");
    Asm("          adi     8");
    Asm("          str     rd");
    Asm("tobcdlp3a: inc     rd");
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
    Asm("          str     rd");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldx");
    Asm("          phi     rd");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp4: lda     rd");
    Asm("          str     r2");
    Asm("          ldn     rd");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          ldn     r2");
    Asm("          shlc");
    Asm("          ani     0fh");
    Asm("          dec     rd");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp4");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldx");
    Asm("          phi     rd");
    Asm("          dec     r9");
    Asm("          glo     r9");
    Asm("          lbnz    tobcdlp2");
    Asm("          sep     sret");

    /* *************************************************** */
    /* ***** Output 16-bit integer                   ***** */
    /* ***** RC - 16-bit integer                     ***** */
    /* *************************************************** */
    if (passNumber == 1) lblItoA = address;
    Asm("itoa:     glo     r2");
    Asm("          smi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          smbi    0");
    Asm("          phi     r2");
    Asm("          glo     r2");
    Asm("          plo     rd");
    Asm("          ghi     r2");
    Asm("          phi     rd");
    Asm("          inc     rd");
    Asm("          ghi     rc");
    Asm("          shl");
    Asm("          lbnf    itoa1");
    Asm("          ldi     '-'");
    Asm("          sep     scall");
    Asm("          dw      f_type");
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
    Asm("          plo     rd");
    Asm("          ghi     r2");
    Asm("          phi     rd");
    Asm("          inc     rd");
    Asm("          ldi     5");
    Asm("          plo     r8");
    Asm("          ldi     4");
    Asm("          phi     r8");
    Asm("itoalp1:  lda     rd");
    Asm("          lbz     itoaz");
    Asm("          str     r2");
    Asm("          ldi     0");
    Asm("          phi     r8");
    Asm("          ldn     r2");
    Asm("itoa2:    adi     030h");
    Asm("          sep     scall");
    Asm("          dw      f_type");
    Asm("itoa3:    dec     r8");
    Asm("          glo     r8");
    Asm("          lbnz    itoalp1");
    Asm("          glo     r2");
    Asm("          adi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          adci    0");
    Asm("          phi     r2");
    Asm("          sep     sret");
    Asm("itoaz:    ghi     r8");
    Asm("          lbz     itoa2");
    Asm("          smi     1");
    Asm("          phi     r8");
    Asm("          lbr     itoa3");
    }


/*
  if (useHeap) {
    }
*/




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
  t1 = variableRAM + iBufferSize + (2 * numberOfVariables);
  t2 = getVariable("FREE_");
  Asm("          ldi  [free_].1");
  Asm("          phi  rf");
  Asm("          ldi  [free_].0");
  Asm("          plo  rf");
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
  if ((useItoA || useAtoI) && useElfos == 0) {
    Asm("          sep  scall");
    Asm("          dw   f_setbd");
    }
  showCompiler = ctmp;
  }

