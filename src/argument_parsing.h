#ifndef ARGS_H
#define ARGS_H
#endif

#include <stdint.h>

struct 	opt /*struct tu put arguments from command line in it*/
{
	uint64_t ram_size;
	int log_level;
	struct file *first_file;
};
struct file
{
	uint64_t addr;
	char *fname;
	struct file *next;
};


void parse_argv(int argc, char *argv[], struct opt *options);
void parse_file(char *str, struct file *ret);
void free_opt(struct opt *options);
