#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ram.h"

// init
uint8_t ram_init(struct ram *memory, uint64_t size)
{
	memory->size=size;
	printf("Allocating %llu bytes...\n", memory->size);
	memory->data_array=calloc(memory->size, sizeof(uint8_t));
	if(memory->data_array==0)
	{
		printf("Error : unable to allocate memory\n");
		exit(1);
	};
	printf("Memory succesfully allocated.\n");
	return 0;
}

// free
void ram_free(struct ram *memory) /*like the previous one but it free the ram*/
{
	printf("Freeing memory (%d bytes)... ", (int)memory->size); /*dirty logging*/
	free ((void *)memory->data_array); /*freeing the memory*/
	printf("OK\n"); /*dirty logging*/
}

// read/write
uint8_t ram_write(struct ram *memory, uint64_t addr, uint8_t data, uint8_t verbose) /*write a byte at a specific address*/
{
	if(verbose){printf("RAM : writing %d at %d... ", data, addr);}
	if(addr>memory->size)
	{
		printf("Unable to write at %d : highest address is %d \n", addr, memory->size);
		return 1;
	}
	memory->data_array[addr]=data;
	if(verbose){printf("OK\n");};
	return 1;
}

// read/write buffer
