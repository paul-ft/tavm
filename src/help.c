#include <stdio.h>

void print_help()
{
	printf("Usage : tavm -m <memory in bytes> (-l) <log level> | [-h] \n [-h] -> help \n [-l] ->  set log level : trace (0), debug (1), info(2 - default), warn (3), erorr (4), fatal (5), disable (6)\nFor more informations, please refer to documentations (wip).\n");
}
