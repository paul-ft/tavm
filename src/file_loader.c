#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"
#include "log.c/src/log.h"
#include "argument_parsing.h"

void load_file_in_ram(struct ram *memory, uint64_t addr, uint8_t *file_name)
{
	log_trace("Loading file %s at %llu", file_name, addr);
	FILE *file=fopen((char *)file_name, "r");
	if(file==NULL)
	{
		log_error("Unable to open %s", file_name);
	}
	int i=0;
	int a=1;
	while(a!=EOF)
	{
		a=fgetc(file);
		if(a==EOF){break;}
		uint8_t *cause_i_need_a_string = malloc(sizeof(uint8_t));
		*cause_i_need_a_string=(uint8_t)a;
		ram_write(memory, addr+i, cause_i_need_a_string, 1);
		i++;
		free(cause_i_need_a_string);
	}
}

void load_files(struct ram *memory, struct file *first_file)
{
	struct file *cour=first_file;
	while(cour!=NULL)
	{
		load_file_in_ram(memory, cour->addr, (uint8_t*)cour->fname);
		cour=cour->next;
	}
	log_info("Files successfully loaded in ram");
}
