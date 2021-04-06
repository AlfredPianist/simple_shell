#include "header.h"

/**
 * print_memory_hex - Prints memory contents in hexadecimal.
 * @buffer: The buffer to be read.
 * @buffer_size: The size of the buffer.
 */
void print_memory_hex(char *buffer, unsigned long int buffer_size)
{
	unsigned long int counter;

	counter = 0;

	for (counter = 0; counter < buffer_size; counter++)
		printf("%.2x ", buffer[counter]);
	printf("\n");
}

void print_parse(char **command)
{
	unsigned long int counter;

	counter = 0;
	do {
		printf("%.2x\n", command[counter][0]);
		print_memory_hex(command[counter], 1);
		printf("Acaba\n");
	} while (command[counter++] != NULL);

	printf("\n");
}
