#include "header.h"

/**
 * get_input_line - Get one line from stdin (until '\n')
 * @line: The pointer to the future sentence.
 *
 * Return: The input line stored.
 */
char *get_input_line(char *line)
{
	size_t line_size;
	ssize_t char_read;

	line_size = char_read = 0;

	char_read = getline(&line, &line_size, stdin);

	/* if (char_read != -1) */
	/* { */
	/* printf("Line with length %lu = %s", char_read, line); */
	/* } */

	return (line);
}

/**
 * parse_line - Parses a sentence into tokens, its delimiter being ' '
 * @command: The pointer to the array of strings of the future parsed sentence.
 * @line: The input line stored.
 *
 * Return: The parsed sentence.
 */
char **parse_line(char **command, char *line)
{
	/* CHECK MALLOC */
	unsigned int words, letters, counter;

	words = letters = counter = 0;

	while (line[counter] != '\n' && line[counter] != '\0')
	{
		if (line[counter] != ' ' &&
		    (line[counter + 1] == ' ' || line[counter + 1] == '\n' ||
		     line[counter + 1] == '\0'))
			words += 1;
		counter++;
	}

	command = malloc(sizeof(*command) * (words + 1));

	words = 0;
	while (*line != '\n' && *line != '\0')
	{
		if (*line != ' ')
		{
			letters = counter = 0;
			while (line[counter] != ' ' && line[counter] != '\n' &&
			       line[counter] != '\0')
				letters += 1, counter++;

			command[words] = malloc(sizeof(**command) * letters + 1);

			counter = 0;
			while (*line != ' ' && *line != '\n' && *line != '\0')
				command[words][counter++] = *line++;

			command[words++][counter] = '\0';
		}
		else
			line++;
	}
	command[words] = NULL;

	return (command);
}
