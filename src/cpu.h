#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#endif

struct instruction
{
	uint8_t opcode;
	uint8_t condition;
	uint8_t reg1;
	uint8_t reg2;
	uint8_t reg3;
	uint64_t var;
};

void exec(struct ram *memory, uint64_t *registers);
