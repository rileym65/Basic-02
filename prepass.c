#include "header.h"

int prepass(char* filename) {
  int   i;
  char  qt;
  FILE *source;
  source = fopen(filename,"r");
  if (source == NULL) {
    printf("Could not open %s\n",filename);
    exit(1);
    }
  useAbs = 0;
  useAdd = 0;
  useSub = 0;
  useMul = 0;
  useDiv = 0;
  useMod = 0;
  useAnd = 0;
  useOr = 0;
  useXor = 0;
  useAtoI = 0;
  useItoA = 0;
  useCmp = 0;
  useEq = 0;
  useNe = 0;
  useGt = 0;
  useLt = 0;
  useEf = 0;
  useRnd = 0;
  useNext = 0;
  useStep = 0;
  useData = 0;
  useHeap = 0;
  useAbs32 = 0;
  useAdd32 = 0;
  useAnd32 = 0;
  useAtoI32 = 0;
  useCmp32 = 0;
  useDiv32 = 0;
  useEq32 = 0;
  useIComp32 = 0;
  useIComp32 = 0;
  useItoA32 = 0;
  useMul32 = 0;
  useNeg32 = 0;
  useNext32 = 0;
  useNull32 = 0;
  useOr32 = 0;
  useRnd32 = 0;
  useSgn32 = 0;
  useShl32 = 0;
  useShr32 = 0;
  useStep32 = 0;
  useSub32 = 0;
  useXor32 = 0;
  useZero32 = 0;
  useAbsFp = 0;
  useAddFp = 0;
  useDivFp = 0;
  useEqFp = 0;
  useGtFp = 0;
  useGteFp = 0;
  useLtFp = 0;
  useLteFp = 0;
  useMulFp = 0;
  useNeFp = 0;
  useSgnFp = 0;
  useSubFp = 0;
  useFtoA = 0;
  useAtoF = 0;
  useCos = 0;
  useExp = 0;
  useLn = 0;
  useSin = 0;
  useTan = 0;
  useTrig = 0;

  lblAtoI = 0;
  lblAbs = 0;
  lblAdd = 0;
  lblAnd = 0;
  lblCmp = 0;
  lblDiv = 0;
  lblEf = 0;
  lblEq = 0;
  lblFalse = 0;
  lblGt = 0;
  lblGte = 0;
  lblItoA = 0;
  lblToBcd = 0;
  lblLt = 0;
  lblLte = 0;
  lblMdNorm = 0;
  lblMod = 0;
  lblMul = 0;
  lblNe = 0;
  lblNext = 0;
  lblNextVar = 0;
  lblOr = 0;
  lblReturn = 0;
  lblRnd = 0;
  lblScall = 0;
  lblSgn = 0;
  lblSret = 0;
  lblStart = 0;
  lblSub = 0;
  lblTrue = 0;
  lblXor = 0;

  while (fgets(currentLine, 1023, source) != NULL) {
    while (strlen(currentLine) > 0 && currentLine[strlen(currentLine)-1] < 32) currentLine[strlen(currentLine)-1] = 0;
    if (strlen(currentLine) > 0) {
      qt = 0;
      for (i=0; i<strlen(currentLine); i++) {
        if (currentLine[i] == '"') qt = 1-qt;
        if (qt == 0) {
          if (useFp) {
            if (strncasecmp(currentLine+i,"cos(",4) == 0) { useCos = -1; useSin = -1; useTrig = -1; }
            if (strncasecmp(currentLine+i,"exp(",4) == 0) { useExp = -1; useTrig = -1; }
            if (strncasecmp(currentLine+i,"ln(",3) == 0) { useLn = -1; useTrig = -1; }
            if (strncasecmp(currentLine+i,"sin(",4) == 0) { useSin = -1; useTrig = -1; }
            if (strncasecmp(currentLine+i,"tan(",4) == 0) { useTan = -1; useCos = -1; useSin = -1; useTrig = -1; }
            }
          if (use32Bits) {
            if (currentLine[i] == '+') useAdd32 = -1;
            if (currentLine[i] == '-') useSub32 = -1;
            if (currentLine[i] == '*') useMul32 = -1;
            if (currentLine[i] == '/') useDiv32 = -1;
            if (currentLine[i] == '%') useMod32 = -1;
            if (currentLine[i] == '&') useAnd32 = -1;
            if (currentLine[i] == '|') useOr32 = -1;
            if (currentLine[i] == '^') useXor32 = -1;
            if (currentLine[i] == '=') useEq32 = -1;
            if (currentLine[i] == '<' && currentLine[i+1] == '>') useNe32 = -1;
            if (currentLine[i] == '<' && currentLine[i+1] == '=') useLte32 = -1;
            if (currentLine[i] == '>' && currentLine[i+1] == '=') useGte32 = -1;
            if (currentLine[i] == '<' && currentLine[i+1] != '>' && currentLine[i+1] != '=') useLt32 = -1;
            if (currentLine[i] == '>' && currentLine[i+1] != '=') useGt32 = -1;
            if (strncasecmp(currentLine+i,"print",5) == 0) useItoA32 = -1;
            if (strncasecmp(currentLine+i,"input",5) == 0) useAtoI32 = -1;
            if (strncasecmp(currentLine+i,"next",4) == 0) useNext32 = -1;
            if (strncasecmp(currentLine+i,"step",4) == 0) useStep32 = -1;
            if (strncasecmp(currentLine+i,"fre(",4) == 0) useSub32 = -1;
            if (strncasecmp(currentLine+i,"sgn(",4) == 0) useSgn32 = -1;
            if (strncasecmp(currentLine+i,"abs(",4) == 0) useAbs32 = -1;
            if (strncasecmp(currentLine+i,"rnd(",4) == 0) useRnd32 = -1;
            }
          else if (useFp) {
            if (strncasecmp(currentLine+i,"print",5) == 0) { useItoA32 = -1; useFtoA; }
            }
          else {
            if (currentLine[i] == '+') useAdd = -1;
            if (currentLine[i] == '-') useSub = -1;
            if (currentLine[i] == '*') useMul = -1;
            if (currentLine[i] == '/') useDiv = -1;
            if (currentLine[i] == '%') useMod = -1;
            if (currentLine[i] == '&') useAnd = -1;
            if (currentLine[i] == '|') useOr = -1;
            if (currentLine[i] == '^') useXor = -1;
            if (currentLine[i] == '=') useEq = -1;
            if (currentLine[i] == '<' && currentLine[i+1] == '>') useNe = -1;
            if (currentLine[i] == '<' && currentLine[i+1] == '=') useLte = -1;
            if (currentLine[i] == '>' && currentLine[i+1] == '=') useGte = -1;
            if (currentLine[i] == '<' && currentLine[i+1] != '>' && currentLine[i+1] != '=') useLt = -1;
            if (currentLine[i] == '>' && currentLine[i+1] != '=') useGt = -1;
            if (strncasecmp(currentLine+i,"print",5) == 0) useItoA = -1;
            if (strncasecmp(currentLine+i,"input",5) == 0) useAtoI = -1;
            if (strncasecmp(currentLine+i,"next",4) == 0) useNext = -1;
            if (strncasecmp(currentLine+i,"step",4) == 0) useStep = -1;
            if (strncasecmp(currentLine+i,"fre(",4) == 0) useSub = -1;
            if (strncasecmp(currentLine+i,"sgn(",4) == 0) useSgn = -1;
            if (strncasecmp(currentLine+i,"abs(",4) == 0) useAbs = -1;
            if (strncasecmp(currentLine+i,"rnd(",4) == 0) useRnd = -1;
            }
          if (strncasecmp(currentLine+i,"dealloc",7) == 0) useHeap = -1;
          if (strncasecmp(currentLine+i,"locate",6) == 0) useItoA = -1;
          if (strncasecmp(currentLine+i,"input",5) == 0) useAtoI = -1;
          if (strncasecmp(currentLine+i,"read",4) == 0) useData = -1;
          if (strncasecmp(currentLine+i,"flg(",4) == 0) useEf = -1;
          if (strncasecmp(currentLine+i,"alloc(",6) == 0) useHeap = -1;
          }
        }
      }
    }
  fclose(source);

  if (useEq || useNe || useGt || useLt || useGte || useLte) useCmp = -1;
  if (useCmp) useSub = -1;
  if (useRnd) useMod = -1;
  if (useRnd32) useMod32 = -1;
  if (useMod) useDiv = -1;
  if (useNext) {
    useSub = -1;
    useAbs = -1;
    }
  if (useStep) {
    useDiv = -1;
    }
  if (useStep32) {
    useDiv32 = -1;
    }
  if (useMul32) {
    useAdd32 = -1;
    useZero32 = -1;
    useShl32 = -1;
    useShr32 = -1;
    }
  if (useMod32) useDiv32 = -1;
  if (useDiv32) {
    useSub32 = -1;
    useNeg32 = -1;
    useComp32 = -1;
    useIComp32 = -1;
    useAdd32 = -1;
    useZero32 = -1;
    useShl32 = -1;
    useShr32 = -1;
    }
  if (useNext32) {
    useSub32 = -1;
    useAbs32 = -1;
    }
  if (useEq32 || useNe32 || useGt32 || useLt32 || useGte32 || useLte32) {
    useCmp32 = -1;
    useComp32 = -1;
    }
  if (useFp) {
    if (useTrig) {
      useMulFp = -1;
      useDivFp = -1;
      useAddFp = -1;
      useSubFp = -1;
      }
    useAbsFp = useAbs32;
    useAddFp = useAdd32;
    useEqFp = useEq32;
    useGtFp = useGt32;
    useGteFp = useGte32;
    useLtFp = useLt32;
    useLteFp = useLte32;
    useNeFp = useNe32;
    useSubFp = useSub32;
    useMulFp = useMul32;
    useDivFp = useDiv32;
    useFtoA = useItoA32;
    useAtoF = useAtoI32;
    useSgnFp = useSgn32;
    if (useSubFp) useAddFp = -1;
    if (useFtoA) {
      useDivFp = -1;
      }
    if (useEqFp || useNeFp || useGtFp || useLtFp || useGteFp || useLteFp) {
      useSubFp = -1;
      useAddFp = -1;
      }
    if (useFtoA) useMulFp = -1;
    }
  if (lblF_inmsg == 0xffff) {
    useAtoI = 0;
    useItoA = 0;
    }
  if (useAtoI == 0 && useItoA == 0) useSelfTerm = 0;
  printf("\n");
  }

