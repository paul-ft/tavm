#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

#include "argument_parsing.h"
#include "help.h"

void parse_argv(int argc, char *argv[], struct opt *options)
{
	int opt=0;
	while ((opt=getopt(argc,argv,"m:l:h"))!=-1)
	{
		switch (opt)
		{
			case 'm' :
				options->ram_size=(uint64_t)atoi(optarg);
				break;
			case 'l' :
				options->log_level=atoi(optarg);
				break;
			case 'h' :
				print_help();
				exit(0);
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
}
