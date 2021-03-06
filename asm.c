/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include "header.h"

typedef struct {
  char opcode[5];
  byte typ;
  byte byte1;
  } OPCODE;

#define OT_0ARG    0
#define OT_1ARG    1
#define OT_LBR     2
#define OT_DB      3
#define OT_DS      4
#define OT_NARG    5
#define OT_EQU     6
#define OT_ORG     7
#define OT_680ARG  8
#define OT_681ARG  9
#define OT_68NARG 10
#define OT_682ARG 11

#define OP_DOT    0x51
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

OPCODE opcodes[] = {
  { "adc",   OT_0ARG,   ADC   },
  { "adci",  OT_1ARG,   ADCI  },
  { "add",   OT_0ARG,   ADD   },
  { "adi",   OT_1ARG,   ADI   },
  { "and",   OT_0ARG,   AND   },
  { "ani",   OT_1ARG,   ANI   },
  { "b1",    OT_1ARG,   B1    },
  { "b2",    OT_1ARG,   B2    },
  { "b3",    OT_1ARG,   B3    },
  { "b4",    OT_1ARG,   B4    },
  { "bdf",   OT_1ARG,   BDF   },
  { "bn1",   OT_1ARG,   BN1   },
  { "bn2",   OT_1ARG,   BN2   },
  { "bn3",   OT_1ARG,   BN3   },
  { "bn4",   OT_1ARG,   BN4   },
  { "bnf",   OT_1ARG,   BNF   },
  { "bnq",   OT_1ARG,   BNQ   },
  { "bnz",   OT_1ARG,   BNZ   },
  { "bq",    OT_1ARG,   BQ    },
  { "br",    OT_1ARG,   BR    },
  { "bz",    OT_1ARG,   BZ    },
  { "db",    OT_DB,     'B'   },
  { "dw",    OT_DB,     'W'   },
  { "dd",    OT_DB,     'D'   },
  { "ds",    OT_DS,     0     },
  { "dec",   OT_NARG,   DEC   },
  { "dis",   OT_0ARG,   DIS   },
  { "equ",   OT_EQU,    0     },
  { "ghi",   OT_NARG,   GHI   },
  { "glo",   OT_NARG,   GLO   },
  { "idl",   OT_0ARG,   IDL   },
  { "inc",   OT_NARG,   INC   },
  { "inp",   OT_NARG,   INP   },
  { "irx",   OT_0ARG,   IRX   },
  { "lda",   OT_NARG,   LDA   },
  { "lbdf",  OT_LBR,    LBDF  },
  { "lbnf",  OT_LBR,    LBNF  },
  { "lbnq",  OT_LBR,    LBNQ  },
  { "lbnz",  OT_LBR,    LBNZ  },
  { "lbq",   OT_LBR,    LBQ   },
  { "lbr",   OT_LBR,    LBR   },
  { "lbz",   OT_LBR,    LBZ   },
  { "ldi",   OT_1ARG,   LDI   },
  { "ldn",   OT_NARG,   LDN   },
  { "ldx",   OT_0ARG,   LDX   },
  { "ldxa",  OT_0ARG,   LDXA  },
  { "lsdf",  OT_0ARG,   LSDF  },
  { "lsie",  OT_0ARG,   LSIE  },
  { "lskp",  OT_0ARG,   NLBR  },
  { "lsnf",  OT_0ARG,   LSNF  },
  { "lsnq",  OT_0ARG,   LSNQ  },
  { "lsnz",  OT_0ARG,   LSNZ  },
  { "lsq",   OT_0ARG,   LSQ   },
  { "lsz",   OT_0ARG,   LSZ   },
  { "mark",  OT_0ARG,   MARK  },
  { "nbr",   OT_0ARG,   NBR   },
  { "nlbr",  OT_0ARG,   NLBR  },
  { "nop",   OT_0ARG,   NOP   },
  { "or",    OT_0ARG,   OR    },
  { "ori",   OT_1ARG,   ORI   },
  { "out",   OT_NARG,   OUT   },
  { "phi",   OT_NARG,   PHI   },
  { "plo",   OT_NARG,   PLO   },
  { "req",   OT_0ARG,   REQ   },
  { "ret",   OT_0ARG,   RET   },
  { "sav",   OT_0ARG,   SAV   },
  { "sd",    OT_0ARG,   SD    },
  { "sdb",   OT_0ARG,   SDB   },
  { "sdi",   OT_1ARG,   SDI   },
  { "sdbi",  OT_1ARG,   SDBI  },
  { "sep",   OT_NARG,   SEP   },
  { "seq",   OT_0ARG,   SEQ   },
  { "sex",   OT_NARG,   SEX   },
  { "shl",   OT_0ARG,   SHL   },
  { "shlc",  OT_0ARG,   SHLC  },
  { "shr",   OT_0ARG,   SHR   },
  { "shrc",  OT_0ARG,   SHRC  },
  { "skp",   OT_0ARG,   NBR   },
  { "sm",    OT_0ARG,   SM    },
  { "smb",   OT_0ARG,   SMB   },
  { "smbi",  OT_1ARG,   SMBI  },
  { "smi",   OT_1ARG,   SMI   },
  { "str",   OT_NARG,   STR   },
  { "stxd",  OT_0ARG,   STXD  },
  { "xor",   OT_0ARG,   XOR   },
  { "xri",   OT_1ARG,   XRI   },
  { "org",   OT_ORG,    0     },
  { "rldi",  OT_68NARG, 0xc0  },
  { "rlxa",  OT_68NARG, 0x60  },
  { "rsxd",  OT_68NARG, 0xa0  },
  { "dbnz",  OT_682ARG, 0x20  },
  { "rnx",   OT_68NARG, 0xb0  },
  { "dadd",  OT_680ARG, 0xf4  },
  { "dadi",  OT_681ARG, 0xfc  },
  { "dadc",  OT_680ARG, 0x74  },
  { "daci",  OT_681ARG, 0x7c  },
  { "dsm",   OT_680ARG, 0xf7  },
  { "dsmi",  OT_681ARG, 0xff  },
  { "dsmb",  OT_680ARG, 0x77  },
  { "dsbi",  OT_681ARG, 0x7f  },
  { "bci",   OT_681ARG, 0x3e  },
  { "bxi",   OT_681ARG, 0x3f  },
  { "ldc",   OT_680ARG, 0x06  },
  { "gec",   OT_680ARG, 0x08  },
  { "stpc",  OT_680ARG, 0x00  },
  { "dtc",   OT_680ARG, 0x01  },
  { "stm",   OT_680ARG, 0x07  },
  { "scm1",  OT_680ARG, 0x05  },
  { "scm2",  OT_680ARG, 0x03  },
  { "spm1",  OT_680ARG, 0x04  },
  { "spm2",  OT_680ARG, 0x02  },
  { "etq",   OT_680ARG, 0x09  },
  { "xie",   OT_680ARG, 0x0a  },
  { "xid",   OT_680ARG, 0x0b  },
  { "cie",   OT_680ARG, 0x0c  },
  { "cid",   OT_680ARG, 0x0d  },
  { "dsav",  OT_680ARG, 0x76  },
  { "scal",  OT_682ARG, 0x80  },
  { "sret",  OT_680ARG, 0x90  },
  { "",      0,         0     },
  };

dword asm_numStack[256];
word asm_nstackSize;
byte asm_tokens[64];
byte asm_numTokens;
char *sourceLine;
word lstCount;

void writeOutput() {
  int i;
  byte checksum;
  char outLine[80];
  char temp[16];
  if (outMode == 'R') {
    sprintf(outLine,":%04x",outAddress);
    for (i=0; i<outCount; i++) {
      sprintf(temp," %02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'I') {
    checksum = outCount;
    sprintf(outLine,":%02x",outCount);
    checksum += (outAddress / 256);
    checksum += (outAddress & 0xff);
    sprintf(temp,"%04x00",outAddress);
    strcat(outLine,temp);
    for (i=0; i<outCount; i++) {
      checksum += outBuffer[i];
      sprintf(temp,"%02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    checksum = (checksum ^ 0xff) + 1;
    sprintf(temp,"%02x",checksum);
    strcat(outLine, temp);
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'B') {
    write(outFile, outBuffer, outCount);
    }
  }

void output(byte value) {
  if (compMode == 'A' && (address < ramStart || address > ramEnd)) {
    showError("Address exceeded available RAM");
    exit(1);
    }
  if (compMode == 'O' && (address < romStart || address > romEnd)) {
    showError("Address exceeded available ROM");
    exit(1);
    }
  if (passNumber == 1) {
    if (address > highest) highest = address;
    }
  if (passNumber == 2) {
    if (showCompiler) {
      printf(" %02x",value);
      listCount++;
      if (listCount == 16) {
        printf("\n");
        printf("     ");
        listCount = 0;
        }
      }
    outBuffer[outCount++] = value;
    codeGenerated++;
    if (outCount == 16) {
      writeOutput();
      outCount = 0;
      outAddress = address+1;
      }
    if (createLst != 0) {
      if (lstCount == 4) {
        fprintf(lstFile,"%s\n",sourceLine);
        fprintf(lstFile,"      ");
        }
      else if (lstCount > 4 && (lstCount % 4) == 0) {
        fprintf(lstFile,"\n");
        fprintf(lstFile,"      ");
        }
      fprintf(lstFile,"%02x ",value);
      lstCount++;
      }
    }
  address++;
  }

char* asm_convertNumber(char* buffer, dword* value, byte* success) {
  byte ishex;
  dword val1,val2;
  ishex = 0;
  val1 = 0;
  val2 = 0;
  if (*buffer == 'r' || *buffer == 'R') {
    if (*(buffer+1) == '0') {
      *value = 0;
      *success = 0xff;
      return buffer+2;
      }
    if (*(buffer+1) >= '2' && *(buffer+1) <= '9') {
      *value = *(buffer+1) - '0';
      *success = 0xff;
      return buffer+2;
      }
    if (*(buffer+1) >= 'a' && *(buffer+1) <= 'f') {
      *value = *(buffer+1) - 87;
      *success = 0xff;
      return buffer+2;
      }
    if (*(buffer+1) >= 'A' && *(buffer+1) <= 'F') {
      *value = *(buffer+1) - 55;
      *success = 0xff;
      return buffer+2;
      }
    if (*(buffer+1) == '1') {
      if (*(buffer+2) >= '0' && *(buffer+2) <= '5') {
        *value = *(buffer+2) - 38;
        *success = 0xff;
        return buffer+3;
        }
      else {
        *value = *(buffer+1) - 55;
        *success = 0xff;
        return buffer+2;
        }
      }
    }
  if (*buffer == '\'' && *(buffer+2) == '\'') {
    buffer++;
    *value = *buffer;
    buffer += 2;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '%') {
    buffer++;
    while (*buffer == '1' || *buffer == '0' || *buffer == '_') {
      if (*buffer != '_')
        val1 = (val1 << 1) | (*buffer - '0');
      buffer++;
      }
    *value = val1;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '$') {
    buffer++;
    if ((*buffer >= '0' && *buffer <= '9') ||
        (*buffer >= 'a' && *buffer <= 'f') ||
        (*buffer >= 'A' && *buffer <= 'F'))
      ishex = 0xff;
    else {
      *value = asmAddress;
      *success = 0xff;
      return buffer;
      }
    }
  if (ishex == 0 && (*buffer < '0' || *buffer > '9')) {
    *success = 0;
    return buffer;
    }
  while ((*buffer >= '0' && *buffer <= '9') ||
         (*buffer >= 'a' && *buffer <= 'f') ||
         (*buffer >= 'A' && *buffer <= 'F')) {
      if (*buffer >= '0' && *buffer <= '9') {
        val1 = (val1 * 10) + (*buffer - '0');
        val2 = (val2 << 4) | (*buffer - '0');
        }
      if (*buffer >= 'a' && *buffer <= 'f')
        val2 = (val2 << 4) | (*buffer - 87);
      if (*buffer >= 'A' && *buffer <= 'F')
        val2 = (val2 << 4) | (*buffer - 55);
      buffer++;
    }
  if (*buffer == 'h' || *buffer == 'H') {
    ishex = 0xff;
    buffer++;
    }
  *success = 0xff;
  *value = (ishex != 0) ? val2 : val1;
  return buffer;
  }


int asm_reduce(char last) {
  int op;
  int ret;
  if (asm_numTokens == 0) return 0;
  if (asm_tokens[asm_numTokens-1] != OP_NUM) return 0;
  if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] >= 0x60) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 3;
    ret = 0;
    if (last) ret = -1;
    }
  else if (asm_numTokens > 2 && asm_tokens[asm_numTokens-3] == OP_OP) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 3;
    ret = 0;
    if (asm_numTokens > 0 && asm_tokens[asm_numTokens-1] >= 0x60) ret = -1;
    if (last) ret = -1;
    }
  else if (asm_numTokens > 4 && asm_tokens[asm_numTokens-3] >= 0x10 &&
                            (asm_tokens[asm_numTokens-4] == OP_NUM ||
                             asm_tokens[asm_numTokens-4] == OP_NUMFP)) {
    op   = asm_tokens[asm_numTokens-3];
    asm_numTokens -= 5;
    ret = -1;
    }
  else {
    return 0;
    }
  switch (op) {
    case OP_DOT:
         if (asm_numStack[asm_nstackSize-1] == 0)
           asm_numStack[asm_nstackSize-2] &= 0x00ff;
         else
           asm_numStack[asm_nstackSize-2] >>= 8;
         asm_nstackSize--;
         break;
    case OP_MUL:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] *
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_DIV:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] /
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
    case OP_MOD:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] %
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_ADD:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] +
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_SUB:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] -
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_GT :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] >
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_LT :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] <
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_GTE:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] >=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_LTE:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] <=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_EQ :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] ==
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_NE :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] !=
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_AND:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] &
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_OR :
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] |
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    case OP_XOR:
         asm_numStack[asm_nstackSize-2] =
             asm_numStack[asm_nstackSize-2] ^
             asm_numStack[asm_nstackSize-1];
         asm_nstackSize--;
         break;
    }
  asm_tokens[asm_numTokens++] = 0;
  asm_tokens[asm_numTokens++] = OP_NUM;
  return ret;
  }

void asm_add(int op) {
  if (asm_tokens[asm_numTokens-1] >= 0x10) {
    }
  while (asm_numTokens > 4 && (op & 0xf0) <= (asm_tokens[asm_numTokens-3] & 0xf0)) {
    asm_reduce(0);
    }
  asm_tokens[asm_numTokens++] = op;
  }

char* asm_evaluate(char* buffer) {
  char term;
  int p;
  char token[64];
  int flag;
  int func;
  int parens;
  byte success;
  dword number;
  parens = 0;
  asm_numTokens = 0;
  asm_nstackSize = 0;
  flag = 1;
  while (*buffer == ' ') buffer++;
  if (*buffer == '-' && (*(buffer+1) < '0' || *(buffer+1) > '9')) {
    asm_tokens[asm_numTokens++] = 0;
    asm_tokens[asm_numTokens++] = OP_NUM;
    asm_tokens[asm_numTokens++] = OP_SUB;
    asm_numStack[asm_nstackSize++] = 0;
    buffer++;
    }
  while (*buffer != 0 && flag) {

    while (*buffer == ' ') buffer++;

    func = -1;
    while (func) {
      func = 0;
      while (*buffer == '(') {
        asm_tokens[asm_numTokens++] = OP_OP;
        parens++;
        buffer++;
        func = -1;
        }
      }

    term = 0;

    /* **************************** */
    /* ***** Process constant ***** */
    /* **************************** */
    buffer = asm_convertNumber(buffer, &number, &success);
    if (success != 0) {
      asm_numStack[asm_nstackSize++] = number;
      asm_tokens[asm_numTokens++] = 0;
      asm_tokens[asm_numTokens++] = OP_NUM;
      term = -1;
      }

    if (term == 0) {
      if ((*buffer >= 'a' && *buffer <= 'z') ||
          (*buffer >= 'A' && *buffer <= 'Z')) {
        p = 0;
        while ((*buffer >= 'a' && *buffer <= 'z') ||
               (*buffer >= 'A' && *buffer <= 'Z') ||
               (*buffer >= '0' && *buffer <= '9') ||
                *buffer == '_' || *buffer == '!') {
          token[p++] = *buffer++;
          }
        token[p] = 0;
        asm_numStack[asm_nstackSize++] = getLabel(token);
        asm_tokens[asm_numTokens++] = 0;
        asm_tokens[asm_numTokens++] = OP_NUM;
        term = -1;
        }
      }

    if (term == 0) {
      showError("<ASM>Expression error, invalid term");
      exit(1);
      }

    while (*buffer == ' ') buffer++;
    while (*buffer == ')' && parens > 0) {
      parens--;
      while (asm_reduce(0)) ;
      buffer++;
      }
    while (*buffer == ' ') buffer++;

    if (*buffer == '+') { asm_add(OP_ADD); buffer++; }
    else if (*buffer == '-') { asm_add(OP_SUB); buffer++; }
    else if (*buffer == '*') { asm_add(OP_MUL); buffer++; }
    else if (*buffer == '/') { asm_add(OP_DIV); buffer++; }
    else if (*buffer == '%') { asm_add(OP_MOD); buffer++; }
    else if (*buffer == '&') { asm_add(OP_AND); buffer++; }
    else if (*buffer == '|') { asm_add(OP_OR); buffer++; }
    else if (*buffer == '^') { asm_add(OP_XOR); buffer++; }
    else if (*buffer == '.') { asm_add(OP_DOT); buffer++; }
    else if (*buffer == '<' && *(buffer+1) == '=') { asm_add(OP_LTE); buffer+=2; }
    else if (*buffer == '>' && *(buffer+1) == '=') { asm_add(OP_GTE); buffer+=2; }
    else if (*buffer == '<' && *(buffer+1) == '>') { asm_add(OP_NE); buffer+=2; }
    else if (*buffer == '<') { asm_add(OP_LT); buffer++; }
    else if (*buffer == '>') { asm_add(OP_GT); buffer++; }
    else if (*buffer == '=') { asm_add(OP_EQ); buffer++; }
    else flag = 0;
    }
  while (asm_reduce(-1));
  if (asm_numTokens != 2) {
    showError("<ASM>Expression error, expression does not reduce to 1 value\n");
    exit(1);
    }
  return buffer;
  }

void addDefine(char* define, int value, int redefine) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      if (redefine) {
        defineValues[i] = value;
        return;
        }
      printf("<ASM>Duplicate define: %s\n",define);
      exit(1);
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (int*)malloc(sizeof(int));
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (int*)realloc(defineValues, sizeof(int) * numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(define) + 1);
  strcpy(defines[numDefines-1], define);
  defineValues[numDefines-1] = value;
  }

int getDefine(char* define) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      return defineValues[i];
      }
  return 0;
  }

void addLabel(char* label, word value) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      printf("<ASM>Duplicate label: %s\n",label);
      exit(1);
      }
  numLabels++;
  if (numLabels == 1) {
    labels = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    }
  else {
    labels = (char**)realloc(labels, sizeof(char*) * numLabels);
    labelValues = (word*)realloc(labelValues, sizeof(word) * numLabels);
    }
  labels[numLabels-1] = (char*)malloc(strlen(label) + 1);
  strcpy(labels[numLabels-1], label);
  labelValues[numLabels-1] = value;
  }

word getLabel(char* label) {
  int i;
  if (passNumber == 1) return 0;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      return labelValues[i];
      }
  printf("<ASM>Label not found: %s\n",label);
  exit(1);
  }

void setLabel(char* label, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      labelValues[i] = value;
      return;
      }
  printf("<ASM>Label not found: %s\n",label);
  exit(1);
  }

dword processArgs(char* args) {
  args = asm_evaluate(args);
  return asm_numStack[0];
  }

void processDb(char* args,char typ) {
  dword num;
  args = trim(args);
  while (*args != 0) {
    if (*args == '\'' && *(args+2) != '\'') {
      args++;
      while (*args != 0 && *args != '\'')
        output(*args++);
      if (*args == '\'') args++;
      }
    else {
      args = asm_evaluate(args);
      num = asm_numStack[0];
      if (typ == 'B') output(num & 0xff);
      else if (typ == 'W') {
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      else {
        output(((num & 0xff000000) >> 24) & 0xff);
        output(((num & 0x00ff0000) >> 16) & 0xff);
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      }
    args = trim(args);
    if (*args == ',') {
      args++;
      args = trim(args);
      }
    }
  }

void processDs(word arg) {
  address += arg;
  }

void processOrg(word arg) {
  address = arg;
  }

void Asm(char* line) {
  int   pos;
  char  qt;
  char *orig;
  char  label[32];
  char  opcode[32];
  char  args[128];
  char  buffer[256];
  dword  value;
  FILE* file;
  int   i;
  orig = line;
  sourceLine = line;
  if (numNests > 0) {
    if (strncasecmp(line,"#else",5) == 0 && nests[numNests-1] != 'I') {
      nests[numNests-1] = (nests[numNests-1] == 'Y') ? 'N' : 'Y';
      return;
      }
    if (nests[numNests-1] != 'Y' && strncasecmp(line,"#ifdef",6) == 0) {
      nests[numNests++] = 'I';
      return;
      }
    if (strncasecmp(line,"#endif",6) == 0) {
      numNests--;
      if (numNests < 0) {
        showError("<ASM> #endif without #if");
        exit(1);
        }
      return;
      }
    if (nests[numNests-1] != 'Y') return;
    }
  if (*line == '#') {
    if (strncasecmp(line,"#define",7) == 0) {
      line += 7;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      line = trim(line);
      i = atoi(line);
      if (i == 0) i = 1;
      addDefine(label, i, 0);
      return;
      }
    if (strncasecmp(line,"#ifdef",6) == 0) {
      line += 6;
      line = trim(line);
      pos = 0;
      while (*line != 0 && *line > ' ') label[pos++] = *line++;
      label[pos] = 0;
      if (getDefine(label)) {
        nests[numNests++] = 'Y';
        }
      else {
        nests[numNests++] = 'N';
        }
      return;
      }
    }

  if (strncasecmp(line, "#include",8) == 0) {
    line += 8;
    while (*line == ' ' || *line == 9) line++;
    file = fopen(line,"r");
    if (file == NULL) {
      printf("Could not open include file: %s\n",line);
      exit(1);
      }
    while (fgets(buffer, 256, file) != NULL) {
      while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < 32)
        buffer[strlen(buffer)-1] = 0;
      Asm(buffer);
      }
    fclose(file);
    return;
    }

  asmAddress = address;
  if (passNumber == 2) {
    if (showAsm) printf("%s\n",line);
    if (useAsm) {
      write(asmFile, line, strlen(line));
      write(asmFile, lineEnding, strlen(lineEnding));
      }
    }
  strcpy(label,"");
  strcpy(opcode,"");
  strcpy(args,"");
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_' || *line == '!') {
      label[pos++] = *line++;
      }
    label[pos] = 0;
    if (*line != ':') {
      printf("<ASM>Invalid label");
      printf("%s\n",orig);
      exit(1);
      }
    line++;
    }
  line = trim(line);
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9')) {
      opcode[pos++] = *line++;
      }
    opcode[pos] = 0;
    }
  line = trim(line);
  pos = 0;
  qt = 0;
  while (((qt == 0 && *line != ';') || qt) && *line != 0) {
    if (*line == '\'') qt = 1 - qt;
    args[pos++] = *line++;
    }
  args[pos] = 0;
  if (passNumber == 1 && strlen(label) > 0) {
    addLabel(label, address);
    }
  if (strlen(opcode) > 0) {
    if (passNumber == 2 && createLst != 0) fprintf(lstFile, "%04x: ",asmAddress);
    lstCount = 0;
    i = 0;
    pos = -1;
    while (pos < 0 && opcodes[i].opcode[0] != 0) {
      if (strcasecmp(opcode, opcodes[i].opcode) == 0) pos = i;
      i++;
      }
    if (pos < 0) {
      printf("<ASM>Unknown opcode: %s\n",opcode);
      exit(1);
      }
    switch (opcodes[pos].typ) {
      case OT_0ARG:
           output(opcodes[pos].byte1);
           break;
      case OT_1ARG:
           output(opcodes[pos].byte1);
           output(processArgs(args) & 0xff);
           break;
      case OT_NARG:
           output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
           break;
      case OT_DB:
           processDb(args,opcodes[pos].byte1);
           break;
      case OT_DS:
           processDs(processArgs(args));
           break;
      case OT_ORG:
           processOrg(processArgs(args));
           break;
      case OT_EQU:
           value = processArgs(args);
           setLabel(label, value);
           break;
      case OT_LBR:
           value = processArgs(args);
           output(opcodes[pos].byte1);
           output(value/256);
           output(value%256);
           break;
      case OT_680ARG:
           if (use1805 == 0) {
             printf("<ASM>1805 Instruction used while not in 1805 mode\n");
             exit(1);
             }
           output(0x68);
           output(opcodes[pos].byte1);
           break;
      case OT_681ARG:
           if (use1805 == 0) {
             printf("<ASM>1805 Instruction used while not in 1805 mode\n");
             exit(1);
             }
           output(0x68);
           output(opcodes[pos].byte1);
           output(processArgs(args) & 0xff);
           break;
      case OT_68NARG:
           if (use1805 == 0) {
             printf("<ASM>1805 Instruction used while not in 1805 mode\n");
             exit(1);
             }
           output(0x68);
           output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
           break;
      default:
           printf("<ASM>Unknown instruction type: %d\n",opcodes[pos].typ);
           exit(1);
           break;
      }
    if (passNumber == 2 && createLst != 0) {
      if (lstCount <= 4) {
        while (lstCount < 4) {
          fprintf(lstFile,"   ");
          lstCount++;
          }
        fprintf(lstFile,"%s",sourceLine);
        }
      fprintf(lstFile, "\n");
      }
    }
  }

