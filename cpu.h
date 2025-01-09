#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_BUF_SIZE 100
#define MAX_INSTRUCTION_COUNT 20
#define REG_COUNT 7

// CPU structure
typedef struct {
    int WSR;
    int IP;
    int RAM[256];
    int R[REG_COUNT];
} cpu;

// Temporary registers for tracking states
typedef struct {
    int reg[REG_COUNT];
} tmpregs;

extern tmpregs regs[MAX_INSTRUCTION_COUNT];
extern int reg_ind;
extern FILE* stream;
extern FILE* disc;
extern cpu obj;
extern char buf[MAX_BUF_SIZE];
extern int s_ind;
extern char number[10];
extern int address;
extern int d_ind;
extern int flag;
extern int N;

// Function declarations
void START();
void EXIT();
bool check_if_valid_alu();
void add();
void sub();
void move();
void ALU();
bool check_if_valid_cu(char* str);
bool check_if_valid_disc();
void store();
void load();
void Disc();
void CU();
void LAYO();

#endif // CPU_H

