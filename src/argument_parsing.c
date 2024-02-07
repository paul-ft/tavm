#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#include "argument_parsing.h"
#include "io.h"
#include "help.h"
#include "log.c/src/log.h"
#include "version.h"

void parse_argv(int argc, char *argv[], struct opt *options)
{
	int opt=0;
	int nin=0;
	int nout=0;
	options->log_level=2;
	struct port *cour;
	options->first_file=malloc(sizeof(struct port));
	while ((opt=getopt(argc,argv,"m:l:hvi:o:b:"))!=-1)
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
			case 'i' :
				if(!nin&&!nout)
				{
					options->first_file->type=INPUT;
					options->first_file->file=fopen(optarg, "r");
					options->first_file->number=0;
					cour=options->first_file;
				}
				else
				{
					struct port *new=malloc(sizeof(struct port));
					new->type=INPUT;
					new->file=fopen(optarg, "r");
					new->number=nin;
					cour->next=new;
					cour=cour->next;
				}
				nin++;
				break;
			case 'o' :
				if(!nin&&!nout)
				{
					options->first_file->type=INPUT;
					options->first_file->file=fopen(optarg, "w");
					options->first_file->number=0;
					cour=options->first_file;
				}
				else
				{
					struct port *new=malloc(sizeof(struct port));
					new->type=INPUT;
					new->file=fopen(optarg, "w");
					new->number=nout;
					cour->next=new;
					cour=cour->next;
				}
				nout++;
				break;
			case 'b' :
				options->boot_device=(uint64_t)atoi(optarg);
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

void free_opt(struct opt *options)
{
	struct port *cour=NULL;
	struct port *next=NULL;
	cour=options->first_file;
	int i=0;
	while(cour!=NULL)
	{
//		log_trace("Freeing file %d (%s)...", i, cour->fname);
		next=cour->next;
		free(cour);
		cour=next;
		i++;
	}
	free(options);
}
