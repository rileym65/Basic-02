#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
#include <unistd.h>
#define O_BINARY 0
#endif


#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#define IDL      0x00
#define LDN      0x00
#define INC      0x10
#define DEC      0x20
#define BR       0x30
#define BQ       0x31
#define BZ       0x32
#define BDF      0x33
#define B1       0x34
#define B2       0x35
#define B3       0x36
#define B4       0x37
#define NBR      0x38
#define BNQ      0x39
#define BNZ      0x3a
#define BNF      0x3b
#define BN1      0x3c
#define BN2      0x3d
#define BN3      0x3e
#define BN4      0x3f
#define LDA      0x40
#define STR      0x50
#define IRX      0x60
#define OUT      0x61
#define INP      0x69
#define RET      0x70
#define DIS      0x71
#define LDXA     0x72
#define STXD     0x73
#define ADC      0x74
#define SDB      0x75
#define SHRC     0x76
#define SMB      0x77
#define SAV      0x78
#define MARK     0x79
#define REQ      0x7a
#define SEQ      0x7b
#define ADCI     0x7c
#define SDBI     0x7d
#define SHLC     0x7e
#define SMBI     0x7f
#define GLO      0x80
#define GHI      0x90
#define PLO      0xa0
#define PHI      0xb0
#define LBR      0xc0
#define LBQ      0xc1
#define LBZ      0xc2
#define LBDF     0xc3
#define NOP      0xc4
#define LSNQ     0xc5
#define LSNZ     0xc6
#define LSNF     0xc7
#define NLBR     0xc8
#define LSKP     0xc8
#define LBNQ     0xc9
#define LBNZ     0xca
#define LBNF     0xcb
#define LSIE     0xcc
#define LSQ      0xcd
#define LSZ      0xce
#define LSDF     0xcf
#define SEP      0xd0
#define SEX      0xe0
#define LDX      0xf0
#define OR       0xf1
#define AND      0xf2
#define XOR      0xf3
#define ADD      0xf4
#define SD       0xf5
#define SHR      0xf6
#define SM       0xf7
#define LDI      0xf8
#define ORI      0xf9
#define ANI      0xfa
#define XRI      0xfb
#define ADI      0xfc
#define SDI      0xfd
#define SHL      0xfe
#define SMI      0xff
#define R0       0x00
#define R1       0x01
#define R2       0x02
#define R3       0x03
#define R4       0x04
#define R5       0x05
#define R6       0x06
#define R7       0x07
#define R8       0x08
#define R9       0x09
#define RA       0x0a
#define RB       0x0b
#define RC       0x0c
#define RD       0x0d
#define RE       0x0e
#define RF       0x0f

#define OP_NUMFP  0x01
#define OP_NUM    0x00

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int   dword;

LINK char   createLst;
LINK word   address;
LINK int    asmFile;
LINK char   asmName[1024];
LINK char   baseName[1024];
LINK char   buffer[2048];
LINK char   compMode;
LINK word   codeGenerated;
LINK dword  *data;
LINK word   dataAddress;
LINK word  *dataLines;
LINK word  *dataPositions;
LINK int    errorCount;
LINK int    exprErrors;
LINK word   numData;
LINK word   numDataLines;
LINK word   iBufferSize;
LINK word   stack;
LINK word   estack;
LINK word   heap;
LINK word   exitAddress;
LINK word   highest;
LINK word   lastLineNumber;
LINK word   lblF_delay;
LINK word   lblF_inmsg;
LINK word   lblF_msg;
LINK word   lblF_setbd;
LINK word   lblF_type;
LINK word   lblF_read;
LINK word   lblF_input;
LINK word   lblStart;
LINK char   currentLine[2048];
LINK word   keyBuffer;
LINK int    lineCount;
LINK char   lineEnding[3];
LINK word   lineNumber;
LINK word   lineNumbers[16384];
LINK word   lineAddresses[16384];
LINK word   listCount;
LINK char   lstName[1024];
LINK char   matches[10][64];
LINK int    matchCount;
LINK word   numberOfLines;
LINK word   numberOfVariables;
LINK word   outAddress;
LINK byte   outBuffer[16];
LINK byte   outCount;
LINK int    outFile;
LINK char   outMode;
LINK char   outName[1024];
LINK int    passNumber;
LINK word   programStart;
LINK word   ramEnd;
LINK word   ramStart;
LINK word   romEnd;
LINK word   romStart;
LINK word   runtime;
LINK byte   SERSEQ;
LINK byte   SERREQ;
LINK byte   SERP;
LINK byte   SERN;
LINK char   showAsm;
LINK char   showCompiler;
LINK char   showList;
LINK char   showOptions;
LINK char   showRuntime;
LINK char   showSymbols;
LINK char   showVariables;
LINK FILE  *source;
LINK char   sourceFile[1024];
LINK int    tokens[64];
LINK int    numTokens;
LINK char   use1805;
LINK byte   useData;
LINK byte   useSelfTerm;
LINK byte   useStep;
LINK byte   useStg;
LINK byte   useTrig;
LINK byte   useElfos;
LINK byte   useAsm;
LINK byte   use32Bits;
LINK byte   useFp;
LINK byte   useStep32;
LINK byte   useStrings;
LINK char **variableNames;
LINK word  *variableAddresses;
LINK char  *variableTypes;
LINK word   variableNextAddress;
LINK word   variableRAM;
LINK word   variableStart;
LINK FILE  *lstFile;

LINK char** defines;
LINK int*   defineValues;
LINK int    numDefines;
LINK char** labels;
LINK word*  labelValues;
LINK int    numLabels;
LINK word   asmAddress;
LINK char   nests[10];
LINK int    numNests;

extern void  Asm(char* line);
extern void  addLabel(char* label, word value);
extern char* casm(char* line);
extern char* cchdir(char* line);
extern char* cclose(char* line);
extern char* ccls(char* line);
extern char* cdata(char* line);
extern char* cdealloc(char* line);
extern char* cdelete(char* line);
extern char* cdma(char* line);
extern char* cdpoke(char* line);
extern char* cend(char* line);
extern char* cexpr(char* line, int etype);
extern char* cfor(char* line);
extern char* cfread(char* line);
extern char* cfwrite(char* line);
extern char* cget(char* line);
extern char* cgosub(char* line);
extern char* cgoto(char* line);
extern char* cidle(char* line);
extern char* cif(char* line);
extern char* cioff(char* line);
extern char* cion(char* line);
extern char* cinput(char* line);
extern char* cintr(char* line);
extern char* clet(char* line);
extern char* clocate(char* line);
extern char* cmkdir(char* line);
extern char* cnext(char* line);
extern int   compileLine(char* line);
extern char* con(char* line);
extern char* copen(char* line);
extern char* cout(char* line);
extern char* cpoke(char* line);
extern char* cpos(char* line);
extern char* cprint(char* line);
extern char* cput(char* line);
extern char* cq(char* line);
extern char* cread(char* line);
extern char* crem(char* line);
extern char* crename(char* line);
extern char* crestore(char* line);
extern char* creturn(char* line);
extern char* crmdir(char* line);
extern int   findLine(word lineNumber, word* address);
extern int   findNextLine(word lineNumber, word* address);
extern int   findNextLineNumber(word lineNumber, word* address);
extern int   findVariable(char* name);
extern word  getHex(char* line);
extern char* getNumber(char* line, word* number);
extern word  getVariable(char* name);
extern void  library();
extern int   match(char* line, char* pattern);
extern void  optionFile(char* filename);
extern void  output(byte value);
extern int   pass(char* filename);
extern int   prepass(char* filename);
extern void  processOption(char* option);
extern void  showError(char* msg);
extern char* trim(char* line);

extern void writeAsm(char* line,char* rem);
extern word getLabel(char* label);
extern void addDefine(char* define, int value, int redefine);
extern int  getDefine(char* define);
extern void writeOutput();

#endif

