#include <stdlib.h>

#include "log.c/src/log.h"
#include "ram.h"
#include "cpu.h"
#include "errors.h"

void exec(struct ram *memory, uint64_t *registers)
{
	log_debug("Executing instruction at  %llx", registers[0x0]);
	struct instruction *inst=malloc(sizeof(struct instruction));
	inst->opcode=memory->data_array[registers[0x0]];
	log_trace("Parsing instruction at %llx -- opcode : %x", registers[0x0], inst->opcode);
	inst->condition=memory->data_array[registers[0x0]+1]>>4;
	log_trace("Parsing instruction at %llx -- condition : %x", registers[0x0], inst->condition);
	inst->reg1=memory->data_array[registers[0x0]+1]-(inst->condition<<4);
	log_trace("Parsing instruction at %llx -- register 1 : %x", registers[0x0], inst->reg1);
	inst->reg2=memory->data_array[registers[0x0]+2]>>4;
	log_trace("Parsing instruction at %llx -- register 2 : %x", registers[0x0], inst->reg2);
	inst->reg3=memory->data_array[registers[0x0]+2]-(inst->reg2<<4);
	log_trace("Parsing instruction at %llx -- register 3 : %x", registers[0x0], inst->reg3);
	uint8_t tmp[8]=
	{
		memory->data_array[registers[0x0]+3],
		memory->data_array[registers[0x0]+4],
		memory->data_array[registers[0x0]+5],
		memory->data_array[registers[0x0]+6],
		memory->data_array[registers[0x0]+7],
		memory->data_array[registers[0x0]+8],
		memory->data_array[registers[0x0]+9],
		memory->data_array[registers[0x0]+10]
	};
	for(int i=0;i<8;i++)
	{
		inst->var=inst->var<<8|tmp[i];
	}
	log_trace("Parsing instruction at %llx -- var : %llx", registers[0x0], inst->var);
	exec_instruction(memory, registers, inst);
	registers[0x0]++;
}

void exec_instruction(struct ram *memory, uint64_t *registers, struct instruction *inst)
{
	switch (inst->opcode)
	{
		case 0x00 :
		{
			log_trace("Instruction : load");
			uint8_t *str=ram_read(memory, inst->var, 1);
			registers[inst->reg1]=(uint64_t)str[1];
			break;
		}
		case 0x01 :
		{
			uint8_t a=(uint8_t)registers[inst->reg1];
			uint8_t arr[]={a};
			ram_write(memory, inst->var, arr, 1);
			break;
		}
		case 0x02 :
		{
			registers[inst->reg1]=registers[inst->reg2];
			break;
		}
		case 0x03 :
		{
			registers[inst->reg1]=inst->var;
			break;
		}
		case 0x04 :
		{
			registers[1]++;
			memory->data_array[registers[1]]=inst->reg1;
			break;
		}
		case 0x05 :
		{
			memory->data_array[registers[1]]=0x0;
			registers[1]--;
			break;
		}
		case 0x10:
		{
			registers[inst->reg1]=~registers[inst->reg2];
			break;
		}
		case 0x11 :
		{
			registers[inst->reg1]=registers[inst->reg2]>>registers[inst->reg3];
			break;
		}
		case 0x12 :
		{
			registers[inst->reg1]=registers[inst->reg2]<<registers[inst->reg3];
			break;
		}
		case 0x13 :
		{
			registers[inst->reg1]=registers[inst->reg2]&registers[inst->reg3];
			break;
		}
		case 0x14 :
		{
			registers[inst->reg1]=registers[inst->reg2]|registers[inst->reg3];
			break;
		}
		case 0x15 :
		{
			registers[inst->reg1]=registers[inst->reg2]^registers[inst->reg3];
			break;
		}
		case 0x20 :
		{
			registers[inst->reg1]=registers[inst->reg2]++;
			break;
		}
		case 0x21 :
		{
			registers[inst->reg1]=registers[inst->reg2]--;
			break;
		}
		case 0x22 :
		{
			registers[inst->reg1]=registers[inst->reg2]+registers[inst->reg3];
			break;
		}
		case 0x23 :
		{
			if(registers[inst->reg2]<registers[inst->reg3])
			{
				registers[inst->reg1]=registers[inst->reg3]-registers[inst->reg2];
				registers[1]++;
				memory->data_array[registers[1]]=1;
			}
			else
			{
				registers[inst->reg1]=registers[inst->reg2]-registers[inst->reg3];
				registers[1]++;
				memory->data_array[registers[1]]=0;
			}
			break;
		}
		case 0x24 :
		{
			if(inst->reg2==0)
			{
				registers[3]=DIVISION_BY_0;
				break;
			}
			registers[inst->reg1]=registers[inst->reg2]/registers[inst->reg3];
			registers[1]++;
			memory->data_array[registers[4]]=registers[inst->reg2]/registers[inst->reg2];
			break;
		}
		case 0x25 :
		{
			registers[inst->reg1]=registers[inst->reg2]%registers[inst->reg3];
			break;
		}
		case 0x30 :
		{
			log_trace("Instruction : true");
			registers[4]=1;
			break;
		}
		case 0x31 :
		{
			registers[4]=0;
			break;
		}
		case 0x32 :
		{
			if(registers[inst->reg1]==registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0x33 :
		{
			if(registers[inst->reg1]!=registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0x34 :
		{
			if(registers[inst->reg1]<registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0x35 :
		{
			if(registers[inst->reg1]<=registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0x36 :
		{
			if(registers[inst->reg1]>registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0x37 :
		{
			if(registers[inst->reg1]>=registers[inst->reg2]){registers[4]=1;}
			else{registers[4]=0;}
			break;
		}
		case 0xFF :
		{
			log_trace("Instruction : break");
			registers[15]=1;
			break;
		}

	}
}
