#include "cpu.h"

int main()
{
	stream = fopen("file","r+");
	if (stream == NULL) {
		stream = fopen("file","w+");
	}

	disc = fopen("disc","r+");

	if (stream == NULL) {
		stream = fopen("file","w+");
	}
	
		

	memset(&obj,0,sizeof(obj));
	fread(&obj,1,sizeof(obj),stream);
	fseek(stream,0,SEEK_SET);

	memset(regs,0,MAX_INSTRUCTION_COUNT);
	for (int i = 0; i < REG_COUNT; ++i) {
		regs[reg_ind].reg[i] = obj.R[i];
	}
		
	++reg_ind;

	START();

	while(true) {
		memset(buf,0,MAX_BUF_SIZE);
		fgets(buf,MAX_BUF_SIZE,stdin);
		if (strncmp(buf,"ADD ",4) == 0 || strncmp(buf,"SUB ",4) == 0 || strncmp(buf,"MOV ",4) == 0) {
			ALU();	
		}
		else if (strncmp(buf,"LOAD ",5) == 0 || strncmp(buf,"STORE ",6) == 0 || strncmp(buf,"DISC ",5) == 0) {
			CU();
		}
		else if (strncmp(buf,"EXIT",4) == 0) {
			EXIT();
		}
		else if (strncmp(buf,"LAYO",4) == 0) {
			LAYO();
		}
		else {
			printf("Command is not valid.\n");
		}
	}

	return 0;
}
