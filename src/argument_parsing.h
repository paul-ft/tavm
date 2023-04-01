#ifndef ARGS_H
#define ARGS_H
#endif

#include <stdint.h>

struct 	arguments /*struct tu put arguments from command line in it*/
{
	uint64_t ram_size;
	int log_level;
};

struct arguments *parse(int argc, char *argv[]);
