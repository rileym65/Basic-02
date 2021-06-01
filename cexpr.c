#include "header.h"

#define OP_SGN    0x58
#define OP_RND    0x57
#define OP_ABS    0x56
#define OP_INP    0x55
#define OP_DPEEK  0x54
#define OP_FRE    0x53
#define OP_FLG    0x52
#define OP_PEEK   0x51
#define OP_MOD    0x43
#define OP_MUL    0x42
#define OP_DIV    0x41
#define OP_ADD    0x32
#define OP_SUB    0x31
#define OP_GT     0x26
#define OP_LT     0x25
#define OP_GTE    0x24
#define OP_LTE    0x23
#define OP_EQ     0x22
#define OP_NE     0x21
#define OP_AND    0x13
#define OP_OR     0x12
#define OP_XOR    0x11
#define OP_OP     0x08
#define OP_CP     0x09
#define OP_NUM    0x00
int     tokens[64];
int     numTokens;

int reduce(char last) {
  int i;
  int arg1,arg2;
  int op;
  int done;
  int flag;
  int ret;
  word addr;
  flag = 0;
  if (numTokens == 0) return 0;
  if (tokens[numTokens-1] != OP_NUM) return 0;
  if (numTokens > 2 && tokens[numTokens-3] >= 0x50) {
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (last) ret = -1;
    }
  else if (numTokens > 2 && tokens[numTokens-3] == OP_OP) {
    arg1 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    numTokens -= 3;
    ret = 0;
    if (numTokens > 0 && tokens[numTokens-1] >= 0x50) ret = -1;
    if (last) ret = -1;
    }
  else if (numTokens > 4 && tokens[numTokens-3] >= 0x10 &&
                            tokens[numTokens-4] == OP_NUM) {
    arg2 = tokens[numTokens-2];
    op   = tokens[numTokens-3];
    arg1 = tokens[numTokens-5];
    numTokens -= 5;
    ret = -1;
    }
  else {
    return 0;
    }
  switch (op) {
    case OP_SGN:
         output(SEP+R4); output(lblSgn/256); output(lblSgn%256);
         break;
    case OP_RND:
         output(SEP+R4); output(lblRnd/256); output(lblRnd%256);
         break;
    case OP_ABS:
         output(SEP+R4); output(lblAbs/256); output(lblAbs%256);
         break;
    case OP_MUL:
         output(SEP+R4); output(lblMul/256); output(lblMul%256);
         break;
    case OP_DIV:
         output(SEP+R4); output(lblDiv/256); output(lblDiv%256);
         break;
    case OP_MOD:
         output(SEP+R4); output(lblMod/256); output(lblMod%256);
         break;
    case OP_ADD:
         output(SEP+R4); output(lblAdd/256); output(lblAdd%256);
         break;
    case OP_SUB:
         output(SEP+R4); output(lblSub/256); output(lblSub%256);
         break;
    case OP_GT :
         output(SEP+R4); output(lblGt/256); output(lblGt%256);
         break;
    case OP_LT :
         output(SEP+R4); output(lblLt/256); output(lblLt%256);
         break;
    case OP_GTE:
         output(SEP+R4); output(lblGte/256); output(lblGte%256);
         break;
    case OP_LTE:
         output(SEP+R4); output(lblLte/256); output(lblLte%256);
         break;
    case OP_EQ :
         output(SEP+R4); output(lblEq/256); output(lblEq%256);
         break;
    case OP_NE :
         output(SEP+R4); output(lblNe/256); output(lblNe%256);
         break;
    case OP_AND:
         output(SEP+R4); output(lblAnd/256); output(lblAnd%256);
         break;
    case OP_OR :
         output(SEP+R4); output(lblOr/256); output(lblOr%256);
         break;
    case OP_XOR:
         output(SEP+R4); output(lblXor/256); output(lblXor%256);
         break;
    case OP_PEEK:
         output(INC+R7);
         output(LDA+R7);
         output(PLO+RF);
         output(LDN+R7);
         output(PHI+RF);
         output(LDI); output(0);
         output(STR+R7);
         output(DEC+R7);
         output(LDN+RF);
         output(STR+R7);
         output(DEC+R7);
         break;
    case OP_DPEEK:
         output(INC+R7);
         output(LDA+R7);
         output(PLO+RF);
         output(LDN+R7);
         output(PHI+RF);
         output(LDA+RF);
         output(STR+R7);
         output(DEC+R7);
         output(LDN+RF);
         output(STR+R7);
         output(DEC+R7);
         break;
    case OP_FLG:
         output(INC+R7);
         output(INC+R7);
         output(LDI); output(0); output(STR+R7); output(DEC+R7);
         output(SEP+R4); output(lblEf/256); output(lblEf%256);
         output(STR+R7); output(DEC+R7);
         break;
    case OP_FRE:
         addr = variableRAM + iBufferSize + (2 * numberOfVariables);
         output(INC+R7);
         output(INC+R7);
         output(GHI+R7); output(STR+R7); output(DEC+R7);
         output(GLO+R7); output(STR+R7); output(DEC+R7);
         output(LDI); output(addr/256); output(STR+R7); output(DEC+R7);
         output(LDI); output(addr%256); output(STR+R7); output(DEC+R7);
         output(SEP+R4); output(lblSub/256); output(lblSub%256);
         break;
    case OP_INP:
         output(LDI); output(SEP+R3);
         output(STXD);
         output(INC+R7);
         output(LDA+R7);
         output(ANI); output(7);
         output(ADI); output(0x68);
         output(STXD);
         output(GLO+R2); output(PLO+RF);
         output(GHI+R2); output(PHI+RF);
         output(INC+RF);
         output(SEP+RF);
         output(LDI); output(0);
         output(STR+R7); output(DEC+R7);
         output(LDX);
         output(STR+R7); output(DEC+R7);
         break;
    }
  tokens[numTokens++] = 0;
  tokens[numTokens++] = OP_NUM;
  return ret;
  }

void add(int op) {
  if (tokens[numTokens-1] >= 0x10) {
    }
  while (numTokens > 4 && (op & 0xf0) <= (tokens[numTokens-3] & 0xf0)) {
    reduce(0);
    }
  tokens[numTokens++] = op;
  }

char* evaluate(char* buffer) {
  int p;
  char token[64];
  int neg;
  int flag;
  int func;
  int parens;
  word number;
  parens = 0;
  numTokens = 0;
  flag = 1;
  while (*buffer == ' ') buffer++;
  if (*buffer == '-' && (*(buffer+1) < '0' || *(buffer+1) > '9')) {
    tokens[numTokens++] = 0;
    tokens[numTokens++] = OP_NUM;
    tokens[numTokens++] = OP_SUB;
    buffer++;
    }
  while (*buffer != 0 && flag) {

    while (*buffer == ' ') buffer++;

    func = -1;
    while (func) {
      func = 0;
      while (*buffer == '(') {
        tokens[numTokens++] = OP_OP;
        parens++;
        buffer++;
        func = -1;
        }
      if (strncasecmp(buffer,"peek(",5) == 0) {
         tokens[numTokens++] = OP_PEEK;
         tokens[numTokens++] = OP_OP;
         buffer+=5;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"dpeek(",6) == 0) {
         tokens[numTokens++] = OP_DPEEK;
         tokens[numTokens++] = OP_OP;
         buffer+=6;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"flg(",4) == 0) {
         tokens[numTokens++] = OP_FLG;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"fre(",4) == 0) {
         tokens[numTokens++] = OP_FRE;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"inp(",4) == 0) {
         tokens[numTokens++] = OP_INP;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"abs(",4) == 0) {
         tokens[numTokens++] = OP_ABS;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"rnd(",4) == 0) {
         tokens[numTokens++] = OP_RND;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      if (strncasecmp(buffer,"sgn(",4) == 0) {
         tokens[numTokens++] = OP_SGN;
         tokens[numTokens++] = OP_OP;
         buffer+=4;
         parens++;
         func = -1;
         }
      }
    if ((*buffer == '-' && *(buffer+1) >= '0' && *(buffer+1) <= '9') |
        (*buffer >= '0' && *buffer <='9')) {
      neg = (*buffer == '-') ? -1 : 0;
      if (*buffer == '-') buffer++;
      number = 0;
      while (*buffer >= '0' && *buffer <= '9') {
        number = number * 10 + (*buffer - '0');
        buffer++;
        }
      if (neg) {
        number = (number^0xffff) + 1;
        }
      tokens[numTokens++] = 0;
      tokens[numTokens++] = OP_NUM;
      output(LDI); output(number/256); output(STR+R7); output(DEC+R7);
      output(LDI); output(number%256); output(STR+R7); output(DEC+R7);
      }

    else if ((*buffer >= 'a' && *buffer <= 'z') ||
             (*buffer >= 'A' && *buffer <= 'Z')) {
      p = 0;
      while ((*buffer >= 'a' && *buffer <= 'z') ||
             (*buffer >= 'A' && *buffer <= 'Z') ||
             (*buffer >= '0' && *buffer <= '9') ||
              *buffer == '_') {
        token[p++] = *buffer++;
        }
      token[p] = 0;
      tokens[numTokens++] = 0;
      tokens[numTokens++] = OP_NUM;
      number = getVariable(token);
      output(LDI); output(number/256); output(PHI+RF);
      output(LDI); output(number%256); output(PLO+RF);
      output(LDA+RF); output(STR+R7); output(DEC+R7);
      output(LDA+RF); output(STR+R7); output(DEC+R7);
      }
    else {
      printf("Expression error: %s\n",buffer);
      return 0;
      }

    while (*buffer == ' ') buffer++;
    while (*buffer == ')' && parens > 0) {
      parens--;
      while (reduce(0)) ;
      buffer++;
      }

    if (*buffer == '+') { add(OP_ADD); buffer++; }
    else if (*buffer == '-') { add(OP_SUB); buffer++; }
    else if (*buffer == '*') { add(OP_MUL); buffer++; }
    else if (*buffer == '/') { add(OP_DIV); buffer++; }
    else if (*buffer == '%') { add(OP_MOD); buffer++; }
    else if (*buffer == '&') { add(OP_AND); buffer++; }
    else if (*buffer == '|') { add(OP_OR); buffer++; }
    else if (*buffer == '^') { add(OP_XOR); buffer++; }
    else if (*buffer == '<' && *(buffer+1) == '=') { add(OP_LTE); buffer+=2; }
    else if (*buffer == '>' && *(buffer+1) == '=') { add(OP_GTE); buffer+=2; }
    else if (*buffer == '<' && *(buffer+1) == '>') { add(OP_NE); buffer+=2; }
    else if (*buffer == '<') { add(OP_LT); buffer++; }
    else if (*buffer == '>') { add(OP_GT); buffer++; }
    else if (*buffer == '=') { add(OP_EQ); buffer++; }
    else flag = 0;
    }
  while (reduce(-1));
  if (numTokens != 2) printf("Expression error\n");
  output(INC+R7); output(LDA+R7); output(PLO+RC);
  output(LDN+R7); output(PHI+RC);
  return buffer;
  }


char* cexpr(char* line) {
  int   pos;
  word  num;
  char  token[128];
  char *temp;
  char  neg;
  line = trim(line);
  temp = line;

  /* ************************************************* */
  /* ***** If expression is just a single number ***** */
  /* ***** then set RC=to that number            ***** */
  /* ************************************************* */
  if ((*temp == '-' && *(temp+1) >= '0' && *(temp+1) <= '9') ||
      (*temp >= '0' && *temp <= '9')) {
    neg = 0;
    if (*temp == '-') {
      neg = -1;
      temp++;
      }
    num = 0;
    while (*temp >= '0' && *temp <= '9') {
      num = (num * 10) + (*temp - '0');
      temp++;
      }
    if (neg) num = (num ^0xffff) + 1;
    temp=trim(temp);
    if (*temp == ',' || *temp == ';' || *temp == 0) {
      output(LDI); output(num/256); output(PHI+RC);
      output(LDI); output(num%256); output(PLO+RC);
      return temp;
      }
    }

  /* *************************************************** */
  /* ***** If expression is just a single variable ***** */
  /* ***** then retrieve that variable into RC     ***** */
  /* *************************************************** */
  if ((*temp >= 'a' && *temp <= 'z') ||
      (*temp >= 'A' && *temp <= 'Z') ||
      (*temp >= '0' && *temp <= '9') ||
      *temp == '_') {
    pos = 0;
    while ((*temp >= 'a' && *temp <= 'z') ||
           (*temp >= 'A' && *temp <= 'Z') ||
           (*temp >= '0' && *temp <= '9') ||
           *temp == '_') {
      token[pos++] = *temp++;
      }
    token[pos] = 0;
    if (*temp == ',' || *temp == ';' || *temp == 0) {
      num = getVariable(token);
      output(LDI); output(num/256); output(PHI+RF);
      output(LDI); output(num%256); output(PLO+RF);
      output(LDA+RF); output(PHI+RC);
      output(LDA+RF); output(PLO+RC);
      return temp;
      }
    }

  /* **************************************** */
  /* ***** Otherwise process expression ***** */
  /* **************************************** */
  return evaluate(line);
  }

