#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"
#include "log.c/src/log.h"
#include "argument_parsing.h"
#include "io.h"

void load_bootfile_in_ram(struct ram *memory, struct opt *options)
{
	struct port *cour = options->first_file;
	while(cour->number!=options->boot_device || cour->type==OUTPUT)
	{
		cour=cour->next;
	}
	int i=0;
	int a=1;
	while(a!=EOF)
	{
		a=fgetc(cour->file);
		if(a==EOF){break;}
		uint8_t *cause_i_need_a_string = malloc(sizeof(uint8_t));
		*cause_i_need_a_string=(uint8_t)a;
		ram_write(memory, i, cause_i_need_a_string, 1);
		i++;
		free(cause_i_need_a_string);
	}
}
/*
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
*/
