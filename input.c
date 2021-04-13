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
 * parse_line - Parses a sentence into tokens.
 * @line: The input line stored.
 * @delims: The array of delimiters.
 * @ignore: The array of substring delimiters (matched pair).
 *
 * Return: The parsed sentence.
 */
char **parse_line(char *line, char *delims, char *ignore)
{
	unsigned int words = 0, letters = 0, counter = 0;
	char **command = NULL;

	words = count_tokens(line, delims, ignore);
	command = _realloc(command, 0, sizeof(*command) * (words + 1));

	if (command == NULL)
		return (NULL);

	while (line && *line)
	{
		if (!is_delim(*line, delims))
		{
			if (ignore && *line == *ignore)
			{
				letters = is_substring(line, ignore);
				if (letters > 0)
				{
					command[counter++] = substring(line, ignore, letters);
					line += letters + 2;
				}
			}
			else
				command[counter++] = new_token(&line, delims);
		}
		else
			line++;
	}
	command[counter] = NULL;
	return (command);
}
