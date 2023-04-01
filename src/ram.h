#ifndef RAM_H
#define RAM_H
#endif

#include <stdint.h>
// structs :
struct ram /*structure for the ram*/
{
	uint64_t size; /*the size in bytes*/
	uint8_t *data_array; /*the ram in itself*/
};

// functions :
uint8_t ram_init(struct ram *memory, uint64_t size); /*(see ram.c)*/
void ram_free(struct ram *memory); /*(see ram.c)*/
