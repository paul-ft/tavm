#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#include "argument_parsing.h"
#include "help.h"
#include "log.c/src/log.h"
#include "version.h"

void parse_argv(int argc, char *argv[], struct opt *options)
{
	int opt=0;
	int nfiles=0;
	options->log_level=2;
	struct file *cour;
	options->first_file=malloc(sizeof(struct file));
	while ((opt=getopt(argc,argv,"m:l:hvf:"))!=-1)
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
			case 'f' :
				if(!nfiles)
				{
					parse_file(optarg, options->first_file);
					cour=options->first_file;
				}
				else
				{
					struct file *new=malloc(sizeof(struct file));
					parse_file(optarg, new);
					cour->next=new;
					cour=cour->next;
				}
				nfiles++;
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

void parse_file(char *str, struct file *ret)
{
	ret->fname=strtok(str, ":");
	ret->addr=atoi(strtok(NULL,":"));
	ret->next=NULL;
}

void free_opt(struct opt *options)
{
	struct file *cour=NULL;
	struct file *next=NULL;
	cour=options->first_file;
	int i=0;
	while(cour!=NULL)
	{
		log_trace("Freeing file %d (%s)...", i, cour->fname);
		next=cour->next;
		free(cour);
		cour=next;
		i++;
	}
	free(options);
}
