#include "header.h"

char** labels;
word*  labelValues;
int    numLabels = 0;

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
    else if (strcasecmp(token,"$") == 0) num = address;
    else if (strcasecmp(token,"[stack]") == 0) num = stack;
    else if (strcasecmp(token,"[estack]") == 0) num = estack;
    else if (token[0] == '\'' && strlen(token) == 3) num = token[1];
    else if (token[0] == '[') {
      pos = 0;
      while (token[pos+1] != 0 && token[pos+1] != ']') {
        token[pos] = token[pos+1];
        pos++;
        }
      token[pos] = 0;
      num = getVariable(token);
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
  int  pos;
  word num;
  char token[256];
  args = trim(args);
  while (*args != 0) {
    pos = 0;
    while (*args != 0 && *args != ',') {
      token[pos++] = *args++;
      }
    token[pos] = 0;
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
        else {
          output(num/256);
          output(num%256);
          }
        }
      else {
        num = 0;
        pos = 0;
        while (token[pos] >= '0' && token[pos] <= '9') {
          num = (num << 4) + (token[pos] - '0');
          pos++;
          }
        if (token[pos] != 0) {
          printf("<ASM>Unknown data in DB list: %s\n",token);
          exit(1);
          }
        if (typ == 'B') output(num & 0xff);
        else {
          output(num/256);
          output(num%256);
          }
        }
      }
    else {
      num = getLabel(token);
      if (typ == 'B') output(num & 0xff);
      else {
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

void Asm(char* line) {
  int   pos;
  char *orig;
  char  label[32];
  char  opcode[32];
  char  args[128];
  word  value;
  orig = line;
  strcpy(label,"");
  strcpy(opcode,"");
  strcpy(args,"");
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') {
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
  while (*line != ';' && *line != 0) {
    args[pos++] = *line++;
    }
  args[pos] = 0;
  if (passNumber == 1 && strlen(label) > 0) {
    addLabel(label, address);
    }
  if (strlen(opcode) > 0) {
    if (strcasecmp(opcode,"adc") == 0) {
      output(ADC);
      }
    else if (strcasecmp(opcode,"adci") == 0) {
      output(ADCI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"add") == 0) {
      output(ADD);
      }
    else if (strcasecmp(opcode,"adi") == 0) {
      output(ADI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"and") == 0) {
      output(AND);
      }
    else if (strcasecmp(opcode,"ani") == 0) {
      output(ANI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"b1") == 0) {
      output(B1);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"b2") == 0) {
      output(B2);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"b3") == 0) {
      output(B3);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"b4") == 0) {
      output(B4);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bdf") == 0) {
      output(BDF);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bn1") == 0) {
      output(BN1);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bn2") == 0) {
      output(BN2);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bn3") == 0) {
      output(BN3);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bn4") == 0) {
      output(BN4);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bnf") == 0) {
      output(BNF);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bnq") == 0) {
      output(BNQ);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bnz") == 0) {
      output(BNZ);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bq") == 0) {
      output(BQ);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"br") == 0) {
      output(BR);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"bz") == 0) {
      output(BZ);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"db") == 0) {
      processDb(args,'B');
      }
    else if (strcasecmp(opcode,"dw") == 0) {
      processDb(args,'W');
      }
    else if (strcasecmp(opcode,"dec") == 0) {
      output(DEC+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"dis") == 0) {
      output(DIS);
      }
    else if (strcasecmp(opcode,"equ") == 0) {
      value = processArgs(args);
      setLabel(label, value);
      }
    else if (strcasecmp(opcode,"ghi") == 0) {
      output(GHI+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"glo") == 0) {
      output(GLO+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"idl") == 0) {
      output(IDL);
      }
    else if (strcasecmp(opcode,"inc") == 0) {
      output(INC+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"inp") == 0) {
      output(INP+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"irx") == 0) {
      output(IRX);
      }
    else if (strcasecmp(opcode,"lda") == 0) {
      output(LDA+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"lbdf") == 0) {
      value = processArgs(args);
      output(LBDF);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbnf") == 0) {
      value = processArgs(args);
      output(LBNF);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbnq") == 0) {
      value = processArgs(args);
      output(LBNQ);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbnz") == 0) {
      value = processArgs(args);
      output(LBNZ);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbq") == 0) {
      value = processArgs(args);
      output(LBQ);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbr") == 0) {
      value = processArgs(args);
      output(LBR);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"lbz") == 0) {
      value = processArgs(args);
      output(LBZ);
      output(value/256);
      output(value%256);
      }
    else if (strcasecmp(opcode,"ldi") == 0) {
      output(LDI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"ldn") == 0) {
      output(LDN+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"ldx") == 0) {
      output(LDX);
      }
    else if (strcasecmp(opcode,"ldxa") == 0) {
      output(LDXA);
      }
    else if (strcasecmp(opcode,"lsdf") == 0) {
      output(LSDF);
      }
    else if (strcasecmp(opcode,"lsie") == 0) {
      output(LSIE);
      }
    else if (strcasecmp(opcode,"lsnf") == 0) {
      output(LSNF);
      }
    else if (strcasecmp(opcode,"lsnq") == 0) {
      output(LSNQ);
      }
    else if (strcasecmp(opcode,"lsnz") == 0) {
      output(LSNZ);
      }
    else if (strcasecmp(opcode,"lsq") == 0) {
      output(LSQ);
      }
    else if (strcasecmp(opcode,"lsz") == 0) {
      output(LSZ);
      }
    else if (strcasecmp(opcode,"mark") == 0) {
      output(MARK);
      }
    else if (strcasecmp(opcode,"nbr") == 0) {
      output(NBR);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"nlbr") == 0) {
      output(NLBR);
      }
    else if (strcasecmp(opcode,"nop") == 0) {
      output(NOP);
      }
    else if (strcasecmp(opcode,"or") == 0) {
      output(OR);
      }
    else if (strcasecmp(opcode,"ori") == 0) {
      output(ORI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"out") == 0) {
      output(OUT+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"phi") == 0) {
      output(PHI+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"plo") == 0) {
      output(PLO+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"req") == 0) {
      output(REQ);
      }
    else if (strcasecmp(opcode,"ret") == 0) {
      output(RET);
      }
    else if (strcasecmp(opcode,"sav") == 0) {
      output(SAV);
      }
    else if (strcasecmp(opcode,"sd") == 0) {
      output(SD);
      }
    else if (strcasecmp(opcode,"sdb") == 0) {
      output(SDB);
      }
    else if (strcasecmp(opcode,"sdi") == 0) {
      output(SDI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"sdbi") == 0) {
      output(SDBI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"sep") == 0) {
      output(SEP+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"seq") == 0) {
      output(SEQ);
      }
    else if (strcasecmp(opcode,"sex") == 0) {
      output(SEX+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"shl") == 0) {
      output(SHL);
      }
    else if (strcasecmp(opcode,"shlc") == 0) {
      output(SHLC);
      }
    else if (strcasecmp(opcode,"shr") == 0) {
      output(SHR);
      }
    else if (strcasecmp(opcode,"shrc") == 0) {
      output(SHRC);
      }
    else if (strcasecmp(opcode,"sm") == 0) {
      output(SM);
      }
    else if (strcasecmp(opcode,"smb") == 0) {
      output(SMB);
      }
    else if (strcasecmp(opcode,"smbi") == 0) {
      output(SMBI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"smi") == 0) {
      output(SMI);
      output(processArgs(args) & 0xff);
      }
    else if (strcasecmp(opcode,"str") == 0) {
      output(STR+(processArgs(args) & 0xf));
      }
    else if (strcasecmp(opcode,"stxd") == 0) {
      output(STXD);
      }
    else if (strcasecmp(opcode,"xor") == 0) {
      output(XOR);
      }
    else if (strcasecmp(opcode,"xri") == 0) {
      output(XRI);
      output(processArgs(args) & 0xff);
      }
    else { 
      printf("<ASM>Unknown opcode: %s\n",opcode);
      exit(1);
      }
    }
  }
