#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "ram.h"
#include "argument_parsing.h"

int main (int argc, char *argv[])
{
// Parsing argv

	struct arguments *options = malloc(sizeof(struct arguments)); /*creating a struct to keep args (see argument_parsing.h and argument_parsing.c)*/
	options=parse(argc, argv); /*Parsing arguments (see argument_parsing.c)*/
	struct arguments tmp = (struct arguments){.verbose_mode=(uint8_t)options->verbose_mode, .ram_size=(uint64_t)options->ram_size}; /*to keep safe the arguments while calling malloc*/

//Ram init

	struct ram* memory=malloc(sizeof(struct ram)); /*creating a struct for the ram (see ram.h)*/
	options=&(struct arguments){.verbose_mode=tmp.verbose_mode, .ram_size=tmp.ram_size}; /*malloc() at previous line probably broke the options, so lets restore it*/
	ram_init(memory, options->ram_size); /*initializing the memory (see ram.c)*/

// leaving :
	ram_free(memory);
	free((void*)memory);
	sleep(1);
	printf("Goodbye \n"); /*it's important to be polite with the user*/
	return 0; /*no comment needed i guess*/
}
