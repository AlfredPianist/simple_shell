#include "header.h"

/**
 * get_input_line - Get one line from stdin (until '\n')
 * @line: The pointer to the future sentence.
 *
 * Return: The input line stored.
 */
int get_input_line(char **line)
{
	size_t line_size;
	ssize_t char_read;

	line_size = char_read = 0;

	char_read = getline(line, &line_size, stdin);

	return (char_read);
}

/**
 * parse_line - Parses a sentence into tokens, its delimiter being ' '
 * @command: The pointer to the array of strings of the future parsed sentence.
 * @line: The input line stored.
 *
 * Return: The parsed sentence.
 */
char **parse_line(char **command, char *line, char *delims, char *ignore)
{
	unsigned int words = 0, counter = 0;

	words = count_tokens(line, delims, ignore);

	command = NULL;
	command = _realloc(command, 0, sizeof(*command) * (words + 1));
	if (command == NULL)
		return (NULL);

	while (line && *line)
	{
		if (!is_delim(*line, delims))
			command[counter++] = new_token(&line, delims, ignore);
		else
			line++;
	}

	if (command[0] == NULL)
	{
		free(command);
		return (NULL);
	}

	command[counter] = NULL;
	return (command);
}
