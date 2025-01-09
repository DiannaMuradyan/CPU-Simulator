#include "cpu.h"

tmpregs regs[MAX_INSTRUCTION_COUNT];
int reg_ind;
FILE* stream;
FILE* disc;
cpu obj;
char buf[MAX_BUF_SIZE];
int s_ind;
char number[10];
int address;
int d_ind;
int flag;
int N;


void START() {
    char buf[30];
    do {
        memset(buf, 0, 30);
        printf("Please enter START : \n");
        fgets(buf, 30, stdin);
    } while (strncmp(buf, "START", 5) != 0);
    obj.WSR = 1;
    obj.IP = 1;
}

void EXIT() {
    obj.WSR = 0;
    obj.IP = 0;
    fwrite(&obj, 1, sizeof(cpu), stream);
    exit(0);
}

bool check_if_valid_alu() {
    memset(number, 0, sizeof(number));
    char* tmp = buf + 4;
    if (tmp[0] == 'R' && (tmp[1] >= '0' && tmp[1] <= '6')) {
        d_ind = atoi(&tmp[1]);
        if (tmp[2] != ',') {
            printf("Invalid register\n");
            return false;
        }
        tmp += 3;
        if (tmp[0] == 'R' && (tmp[1] >= '0' && tmp[1] <= '6')) {
            flag = 1;
            s_ind = atoi(&tmp[1]);
        }
        else if (tmp[0] >= '0' && tmp[0] <= '9') {
            flag = 2;
            memset(number, 0, 10);
            for (int i = 0; tmp[i] != '\0'; ++i) {
                number[i] = tmp[i];
            }
        }
    }
    else {
        return false;
    }
    return true;
}

void add() {
    if (flag == 1) {
        obj.R[d_ind] += obj.R[s_ind];
    }
    else if (flag == 2) {
        obj.R[d_ind] += atoi(number);
    }
    obj.RAM[d_ind] = obj.R[d_ind];
    for (int i = 0; i < REG_COUNT; ++i) {
        regs[reg_ind].reg[i] = regs[reg_ind - 1].reg[i];
    }
    regs[reg_ind].reg[d_ind] = obj.R[d_ind];
    ++reg_ind;
    ++obj.IP;
}

void sub() {
    if (flag == 1) {
        obj.R[d_ind] -= obj.R[s_ind];
    }
    else {
        obj.R[d_ind] -= atoi(number);
    }

    obj.RAM[d_ind] = obj.R[d_ind];
    for (int i = 0; i < REG_COUNT; ++i) {
        regs[reg_ind].reg[i] = regs[reg_ind - 1].reg[i];
    }
    regs[reg_ind].reg[d_ind] = obj.R[d_ind];
    ++reg_ind;
    ++obj.IP;
}

void move() {
    if (flag == 1) {
        obj.R[d_ind] = obj.R[s_ind];
    }
    else {
        obj.R[d_ind] = atoi(number);
    }

    obj.RAM[d_ind] = obj.R[d_ind];
    for (int i = 0; i < REG_COUNT; ++i) {
        regs[reg_ind].reg[i] = regs[reg_ind - 1].reg[i];
    }
    regs[reg_ind].reg[d_ind] = obj.R[d_ind];

    ++reg_ind;
    ++obj.IP;
}

void ALU() {
    if (check_if_valid_alu()) {
        if (strncmp(buf, "ADD", 3) == 0) {
            add();
        }
        else if (strncmp(buf, "SUB", 3) == 0) {
            sub();
        }
        else {
            move();
        }
    }
    else {
        printf("Is not valid\n");
    }
}

bool check_if_valid_cu(char* str) {
    memset(number, 0, sizeof(number));
    char* tmp = buf + strlen(str) + 1;
    if (tmp[0] == 'R' && (tmp[1] >= '0' && tmp[1] <= '6')) {
        s_ind = atoi(&tmp[1]);
        if (tmp[2] != ',') {
            printf("Invalid register\n");
            return false;
        }
        tmp += 3;
        for (int i = 0; tmp[i] != '\0' && tmp[i] != '\n'; ++i) {
            if (tmp[i] < '0' || tmp[i] > '9') {
                printf("Invalid register\n");
                return false;
            }
            number[i] = tmp[i];
        }
        address = atoi(number);
        if (address < 0 || address > 64) {
            printf("Segmentation fault\n");
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

bool check_if_valid_disc() {
    memset(number, 0, sizeof(number));
    char* tmp = buf + 5;
    for (int i = 0; i != '\0'; ++i) {
        if (tmp[i] < '0' || tmp[i] > '9') {
            return false;
        }
    }

    N = atoi(tmp);

    if (N > obj.IP) {
        return false;
    }

    return true;
}

void store() {
    ++obj.IP;
    obj.RAM[address] = obj.R[s_ind];
}

void load() {
    ++obj.IP;
    obj.R[s_ind] = obj.RAM[address];
    for (int i = 0; i < REG_COUNT; ++i) {
        regs[reg_ind].reg[i] = regs[reg_ind - 1].reg[i];
    }
    regs[reg_ind].reg[s_ind] = obj.R[s_ind];
    ++reg_ind;
}

void Disc() {
    int ind = reg_ind - N;
    for (int i = 0; i < REG_COUNT; ++i) {
        obj.R[i] = regs[ind].reg[i];
    }
    obj.IP -= N;
}

void CU() {
    if (strncmp(buf, "STORE", 5) == 0 && check_if_valid_cu("STORE")) {
        store();
    }
    else if (strncmp(buf, "LOAD", 4) == 0 && check_if_valid_cu("LOAD")) {
        load();
    }
    else if (strncmp(buf, "DISC", 4)) {
        if (check_if_valid_disc()) {
            Disc();
        }
    }
}

void LAYO() {
    printf("CPU state : ");
    for (int i = 0; i < REG_COUNT; ++i) {
        printf("R%d: %d   ", i, obj.R[i]);
    }
    printf("\n\nMemory : [");
    for (int i = 0; i < 64; ++i) {
        printf("%d", obj.RAM[i]);
        if (i != 63) {
            printf(",");
        }
    }
    printf("]  (size 256)\n\n");
    ++obj.IP;
    printf("IP : %d\n", obj.IP);
}

