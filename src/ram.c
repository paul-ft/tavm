#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ram.h"
#include "log.c/src/log.h"

/*init*/
uint8_t ram_init(struct ram *memory, uint64_t size)
{
	log_info("RAM : initializing memory...");
	memory->size=size;
	log_debug("RAM : allocating %llu bytes...", memory->size);
	memory->data_array=calloc(memory->size, sizeof(uint8_t));
	if(memory->data_array==0)
	{
		log_fatal("RAM : unable to allocate memory");
		exit(1);
	};
	log_info("RAM : memory succesfully initialized");
	return 0;
}

/* free*/
void ram_free(struct ram *memory) /*like the previous one but it free the ram*/
{
	log_debug("RAM : freeing memory (%d bytes)... ", (int)memory->size); /*dirty logging*/
	free ((void *)memory->data_array); /*freeing the memory*/
	log_trace("RAM : done\n"); /*dirty logging*/
}

/* read/write*/

uint8_t ram_write(struct ram *memory, uint64_t addr, uint8_t *data, uint64_t lenght)
{
	uint64_t i=0;
	while(i<lenght)
	{
		if(addr+i>memory->size)
		{
			log_debug("Unable to write at %llu : out of memory", addr+i);
			return 1;
		}
		log_trace("Writing %d at %llu", data[i], addr+i);
		memory->data_array[addr+i]=data[i];
		i++;
	}
	return 0;
}

uint8_t *ram_read(struct ram *memory, uint64_t addr, uint64_t lenght)
{
	uint8_t *buffer=calloc(sizeof(uint8_t), lenght);
	uint64_t i=0;
	while(i<lenght)
	{
		if(addr+i>memory->size)
		{
			log_trace("Unable to read at %llu : out of memory", addr+i);
			return buffer;
		}
		else
		{
			log_trace("Reading at %llu", addr+i);
			buffer[i]=memory->data_array[addr+i];
		}
		i++;
	}
	return buffer;
}
