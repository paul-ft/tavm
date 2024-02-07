#ifndef ARGS_H
#define ARGS_H
#endif

#include <stdint.h>
#include <stdio.h>

struct 	opt /*struct tu put arguments from command line in it*/
{
	uint64_t ram_size;
	int log_level;
	struct port *first_file;
	uint64_t boot_device;
};
struct port
{
	FILE *file;
	struct port *next;
	uint8_t type;
	uint64_t number;
};


void parse_argv(int argc, char *argv[], struct opt *options);
void free_opt(struct opt *options);
