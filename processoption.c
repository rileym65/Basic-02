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

void processRAM(char* buffer) {
  ramStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -ram\n");
    exit(1);
    }
  buffer++;
  ramEnd = getHex(buffer);
  }

void processROM(char* buffer) {
  romStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -rom\n");
    exit(1);
    }
  buffer++;
  romEnd = getHex(buffer);
  }

void processOption(char* option) {
    if (strcmp(option,"-32") == 0) use32Bits = -1;
    if (strcmp(option,"-fp") == 0) { useFp = -1; use32Bits = -1; }
    if (strcmp(option,"-1805") == 0) use1805 = -1;
    if (strcmp(option,"-a") == 0) useAsm = -1;
    if (strcmp(option,"-A") == 0) showAsm = -1;
    if (strcmp(option,"-b") == 0) outMode = 'B';
    if (strcmp(option,"-i") == 0) outMode = 'I';
    if (strcmp(option,"-o") == 0) showOptions = -1;
    if (strcmp(option,"-r") == 0) outMode = 'R';
    if (strcmp(option,"-R") == 0) showRuntime = -1;
    if (strcmp(option,"-l") == 0) showList = -1;
    if (strcmp(option,"-L") == 0) createLst = -1;
    if (strcmp(option,"-c") == 0) showCompiler = -1;
    if (strcmp(option,"-s") == 0) showSymbols = -1;
    if (strcmp(option,"-v") == 0) showVariables = -1;
    if (strcmp(option,"-elfos") == 0) {
      useElfos = -1;
      programStart = 0x2000;
      }
    if (strcmp(option,"-stg") == 0) {
      useStg = -1;
      exitAddress = 0x8003;
      ramEnd = 0x7eff;
      }
    if (strcmp(option,"-rq") == 0) {
      SERSEQ = REQ;
      SERREQ = SEQ;
      }
    if (strcmp(option,"-nq") == 0) {
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-lf") == 0) strcpy(lineEnding,"\n");
    if (strcmp(option,"-cr") == 0) strcpy(lineEnding,"\r");
    if (strcmp(option,"-crlf") == 0) strcpy(lineEnding,"\r\n");
    if (strcmp(option,"-lfcr") == 0) strcpy(lineEnding,"\n\r");
    if (strcmp(option,"-ef1") == 0) {
      SERN = BN1;
      SERP = B1;
      }
    if (strcmp(option,"-ef2") == 0) {
      SERN = BN2;
      SERP = B2;
      }
    if (strcmp(option,"-ef3") == 0) {
      SERN = BN3;
      SERP = B3;
      }
    if (strcmp(option,"-ef4") == 0) {
      SERN = BN4;
      SERP = B4;
      }
    if (strcmp(option,"-ref1") == 0) {
      SERN = B1;
      SERP = BN1;
      }
    if (strcmp(option,"-ref2") == 0) {
      SERN = B2;
      SERP = BN2;
      }
    if (strcmp(option,"-ref3") == 0) {
      SERN = B3;
      SERP = BN3;
      }
    if (strcmp(option,"-ref4") == 0) {
      SERN = B4;
      SERP = BN4;
      }
    if (strcmp(option,"-term=bios") == 0) {
      useSelfTerm = 0;
      lblF_inmsg = 0xff66;
      lblF_type = 0xff03;
      lblF_read = 0xff06;
      lblF_input = 0xff0f;
      lblF_msg = 0xff09;
      lblF_setbd = 0xff2d;
      }
    if (strcmp(option,"-term=self") == 0) {
      useSelfTerm = 0xff;
      lblF_inmsg = 0x0000;
      lblF_type = 0x0000;
      lblF_read = 0x0000;
      lblF_input = 0x0000;
      lblF_msg = 0x0000;
      lblF_setbd = 0x0000;
      }
    if (strcmp(option,"-term=none") == 0) {
      useSelfTerm = 0;
      lblF_inmsg = 0xffff;
      lblF_type = 0xffff;
      lblF_read = 0xffff;
      lblF_input = 0xffff;
      lblF_msg = 0xffff;
      lblF_setbd = 0xffff;
      }
    if (strcmp(option,"-melf") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      SERN = BN2;
      SERP = B2;
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-pev") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      SERN = BN2;
      SERP = B2;
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-pev2") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      SERN = B2;
      SERP = BN2;
      SERSEQ = REQ;
      SERREQ = SEQ;
      }
    if (strcmp(option,"-elf2k") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      SERN = BN3;
      SERP = B3;
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-mclo") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      SERN = BN3;
      SERP = B3;
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-mchi") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      SERN = BN3;
      SERP = B3;
      SERSEQ = SEQ;
      SERREQ = REQ;
      }
    if (strcmp(option,"-mchip") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      SERN = B3;
      SERP = BN3;
      SERSEQ = REQ;
      SERREQ = SEQ;
      lblF_inmsg = 0x0f66;
      lblF_type = 0x0f03;
      lblF_read = 0x0f06;
      lblF_input = 0x0f0f;
      lblF_msg = 0x0f09;
      lblF_setbd = 0x0f2d;
      }
    if (strncmp(option,"-start=",7) == 0) programStart=getHex(option+7);
    if (strncmp(option,"-exit=",6) == 0) exitAddress=getHex(option+6);
    if (strncmp(option,"-vars=",6) == 0) variableStart=getHex(option+6);
    if (strncmp(option,"-ram=",5) == 0) processRAM(option+5);
    if (strncmp(option,"-rom=",5) == 0) processROM(option+5);
    if (strncmp(option,"-stack=",7) == 0) stack=getHex(option+7);
    if (strncmp(option,"-estack=",8) == 0) estack=getHex(option+8);
    if (strncmp(option,"-heap=",6) == 0) heap=getHex(option+6);
    if (strncmp(option,"-keybuf=",8) == 0) iBufferSize=getHex(option+8);
  }

