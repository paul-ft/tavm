#ifndef ARGS_H
#define ARGS_H
#endif

#include <stdint.h>

struct 	opt /*struct tu put arguments from command line in it*/
{
	uint64_t ram_size;
	int log_level;
};

void parse_argv(int argc, char *argv[], struct opt *options);
