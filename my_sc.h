#ifndef _GUARD_H_
#define _GUARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 100
#define cmd_num 30

#define EXITOFMEM   1
#define ERRREGVALUE 2
#define ERRREGNUM   3
#define ERRCOMMAND  4

int Memory[SIZE], cmd_arr[cmd_num];
int reg_flags, flag, memoryPointer;

int sc_memoryInit();
int sc_memorySet(int address,int value);
int sc_memoryGet(int address,int *value);
int sc_memoryPrint();
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit();
int sc_regSet(int reg,int value);
int sc_regGet(int reg,int *value);
int compare(const void *a,const void *b);
int sc_commandEncode(int command,int operand,int *value);
int sc_commandDecode(int value,int *command,int *operand);


#endif
