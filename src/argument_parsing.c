#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

#include "argument_parsing.h"
#include "help.h"
#include "log.c/src/log.h"
#include "version.h"

void parse_argv(int argc, char *argv[], struct opt *options)
{
	int opt=0;
	options->log_level=2;
	while ((opt=getopt(argc,argv,"m:l:hv"))!=-1)
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
			case 'v' :
				printf("%s\n", VER);
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
		log_fatal("Unable to boot without ram. Use tavm -h for more informations.\n");
		exit(1);
	}
}
