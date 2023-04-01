#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

#include "argument_parsing.h"
#include "help.h"

struct arguments* parse(int argc, char *argv[])
{
	int opt=0;
	struct arguments *options=&(struct arguments){.ram_size=0, .verbose_mode=0};
	while ((opt=getopt(argc,argv,"m:vh"))!=-1)
	{
		switch (opt)
		{
			case 'm' :
				options->ram_size=(uint64_t)atoi(optarg);
				break;
			case 'v' :
				options->verbose_mode=1;
				break;
			case 'h' :
				print_help();
				exit(1);
				break;
			default :
				print_help();
				exit(1);
				break;
		}
	}
	if(options->ram_size==0)
	{
		printf("Unable to boot without ram.\nUse tavm -h for more informations.\n");
		exit(1);
	}
	return options;
}
