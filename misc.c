#include "header.h"

/**
 * print_parsed_line - Print the parsed line (array of strings).
 * @command: The parsed line.
 */
void print_parsed_line(char **command)
{
	int i;

	printf("Parsed line:\n");
	for (i = 0; command && command[i]; i++)
		printf("%s\n", command[i]);
}
