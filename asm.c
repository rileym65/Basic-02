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

word convertNumber(char* line) {
  word num;
  char* orig;
  orig = line;
  if (line[strlen(line)-1] == 'h' ||
      line[strlen(line)-1] == 'H') {
    line[strlen(line)-1] = 0;
    num = 0;
    while ((*line >= 'a' && *line <= 'f') ||
           (*line >= 'A' && *line <= 'F') ||
           (*line >= '0' && *line <= '9')) {
      if (*line >= '0' && *line <= '9') num = (num << 4) + (*line - '0');
      if (*line >= 'a' && *line <= 'f') num = (num << 4) + (*line - 'a' + 10);
      if (*line >= 'A' && *line <= 'F') num = (num << 4) + (*line - 'A' + 10);
      line++;
      }
    if (*line != 0) {
      printf("<ASM>Unknown character in number: %s\n",orig);
      exit(1);
      }
    return num;
    }
  else {
    num = 0;
    while (*line >= '0' && *line <= '9') {
      num = (num * 10) + (*line - '0');
      line++;
      }
    if (*line != 0) {
      printf("<ASM>Unknown character in number: %s\n",orig);
      exit(1);
      }
    return num;
    }
  }

word processArgs(char* args) {
  word ret;
  char token[128];
  int  pos;
  char op;
  char qt;
  word num;
  args = trim(args);
  ret = 0;
  op = ' ';
  while (*args != 0) {
    pos = 0;
    qt = 0;
    while (*args != 0 && ((qt == 0 && strchr("+-*/&|^.% ",*args) == NULL) || qt)) {
      if (*args == '\'') qt = 1-qt;
      token[pos++] = *args++;
      }
    token[pos] = 0;
    if (strcasecmp(token,"r0") == 0) num = 0;
    else if (strcasecmp(token,"r1") == 0) num = 1;
    else if (strcasecmp(token,"r2") == 0) num = 2;
    else if (strcasecmp(token,"r3") == 0) num = 3;
    else if (strcasecmp(token,"r4") == 0) num = 4;
    else if (strcasecmp(token,"r5") == 0) num = 5;
    else if (strcasecmp(token,"r6") == 0) num = 6;
    else if (strcasecmp(token,"r7") == 0) num = 7;
    else if (strcasecmp(token,"r8") == 0) num = 8;
    else if (strcasecmp(token,"r9") == 0) num = 9;
    else if (strcasecmp(token,"ra") == 0) num = 10;
    else if (strcasecmp(token,"rb") == 0) num = 11;
    else if (strcasecmp(token,"rc") == 0) num = 12;
    else if (strcasecmp(token,"rd") == 0) num = 13;
    else if (strcasecmp(token,"re") == 0) num = 14;
    else if (strcasecmp(token,"rf") == 0) num = 15;
    else if (strcasecmp(token,"r10") == 0) num = 10;
    else if (strcasecmp(token,"r11") == 0) num = 11;
    else if (strcasecmp(token,"r12") == 0) num = 12;
    else if (strcasecmp(token,"r13") == 0) num = 13;
    else if (strcasecmp(token,"r14") == 0) num = 14;
    else if (strcasecmp(token,"$") == 0) num = asmAddress;
    else if (strcasecmp(token,"[stack]") == 0) {
printf("Disallowed use of [stack]\n");
exit(1);
      }
    else if (strcasecmp(token,"[estack]") == 0) {
printf("Disallowed use of [estack]\n");
exit(1);
      }
    else if (strcasecmp(token,"[iobuffer]") == 0) {
printf("Disallowed use of [iobuffer]\n");
exit(1);
      }
    else if (token[0] == '\'' && strlen(token) == 3) num = token[1];
    else if (token[0] == '[') {
printf("Disallowed use of [%s]\n",token);
exit(1);
      }
    else if (token[0] == '<') {
printf("Disallowed use of <%s>\n",token);
exit(1);
      }
    else if (token[0] >= 'a' && token[0] <= 'z') num = getLabel(token);
    else if (token[0] >= 'A' && token[0] <= 'Z') num = getLabel(token);
    else if (token[0] >= '0' && token[0] <= '9') num = convertNumber(token);
    else {
      printf("<ASM>Expression error: %s\n",token);
      exit(1);
      }
    switch (op) {
      case '+': ret += num; break;
      case '-': ret -= num; break;
      case '*': ret *= num; break;
      case '/': ret /= num; break;
      case '%': ret %= num; break;
      case '&': ret &= num; break;
      case '|': ret |= num; break;
      case '^': ret ^= num; break;
      case '.': ret = (num == 0) ? ret & 0xff : ret >> 8; break;
      case ' ': ret = num; break;
      }
    args = trim(args);
    if (*args == '+') op = '+';
    else if (*args == '-') op = '-';
    else if (*args == '*') op = '*';
    else if (*args == '/') op = '/';
    else if (*args == '%') op = '%';
    else if (*args == '&') op = '&';
    else if (*args == '|') op = '|';
    else if (*args == '^') op = '^';
    else if (*args == '.') op = '.';
    else if (*args == 0) op = ' ';
    else {
      printf("<ASM>Invalid operator encountered: %c\n",*args);
      exit(1);
      }
    if (op != ' ') args++;
    args = trim(args);
    }
  return ret;
  }

void processDb(char* args,char typ) {
  int  qt;
  int  pos;
  word num;
  char token[256];
  args = trim(args);
  while (*args != 0) {
    pos = 0;
    qt = 0;
    while (*args != 0 && (*args != ',' || qt != 0)) {
      if (*args == '\'') qt = (qt) ? 0 : 1;
      token[pos++] = *args++;
      }
    token[pos] = 0;
    while (strlen(token) > 0 && token[strlen(token)-1] <= ' ') token[strlen(token)-1] = 0;
    if (token[0] >= '0' && token[0] <= '9') {
      if (token[strlen(token)-1] == 'h' ||
          token[strlen(token)-1] == 'H') {
        token[strlen(token)-1] = 0;
        num = 0;
        pos = 0;
        while ((token[pos] >= 'a' && token[pos] <= 'f') ||
               (token[pos] >= 'A' && token[pos] <= 'F') ||
               (token[pos] >= '0' && token[pos] <= '9')) {
          if (token[pos] >= '0' && token[pos] <= '9') num = (num << 4) + (token[pos] - '0');
          if (token[pos] >= 'a' && token[pos] <= 'f') num = (num << 4) + (token[pos] - 'a' + 10);
          if (token[pos] >= 'A' && token[pos] <= 'F') num = (num << 4) + (token[pos] - 'A' + 10);
          pos++;
          }
        if (token[pos] != 0) {
          printf("<ASM>Unknown data in DB list: %s\n",token);
          exit(1);
          }
        if (typ == 'B') output(num & 0xff);
        else if (typ == 'W') {
          output(num/256);
          output(num%256);
          }
        else {
          output(0);
          output(0);
          output(num/256);
          output(num%256);
          }
        }
      else {
        num = 0;
        pos = 0;
        while (token[pos] >= '0' && token[pos] <= '9') {
          num = (num * 10) + (token[pos] - '0');
          pos++;
          }
        if (token[pos] != 0) {
          printf("<ASM>Unknown data in DB list: %s\n",token);
          exit(1);
          }
        if (typ == 'B') output(num & 0xff);
        else if (typ == 'W') {
          output(num/256);
          output(num%256);
          }
        else {
          output(0);
          output(0);
          output(num/256);
          output(num%256);
          }
        }
      }
    else if (token[0] == '[') {
printf("Disallowed use of [] in DB\n");
      }
    else if (token[0] == '<') {
printf("Disallowed use of <> in DB\n");
      }
    else if (token[0] == '\'') {
      for (pos=0; pos<strlen(token); pos++)
        if (token[pos] != '\'') output(token[pos]);
      }
    else {
      num = getLabel(token);
      if (typ == 'B') output(num & 0xff);
      else if (typ == 'W') {
        output(num/256);
        output(num%256);
        }
      else {
        output(0);
        output(0);
        output(num/256);
        output(num%256);
        }
//      printf("<ASM>Unknown data in DB list: %s\n",token);
//      exit(1);
      }
    
    args = trim(args);
    if (*args == ',') args++;
    args = trim(args);
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
  word  value;
  FILE* file;
  int   i;
  orig = line;
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
    }
  }

