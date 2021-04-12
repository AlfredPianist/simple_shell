#include "test.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: First string to concatenate and the final result.
 * @src: Second string to concatenate.
 *
 * Return: The full concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, size = 0, j = 0;

	while (dest[i++])
		size++;

	for (j = 0; src[j] && j < n; j++, size++)
		dest[size] = src[j];

	dest[size] = '\0';

	return (dest);
}

int is_delim(char curr_char, char *delims)
{
	while (delims && *delims)
		if (curr_char == *delims++)
			return (1);
	return (0);
}

int count_tokens(char *line, char *delims, char *ignore)
{
	int tokens = 0, i = 0;

	ignore = ignore;
	while (line && line[i])
	{
		if (is_delim(line[i], delims) ||
		    (!is_delim(line[i], delims) && !line[i + 1]))
			tokens += 1;
		i++;
	}

	return (tokens);
}

char *new_token(char **line, char *delims, char *ignore)
{
	char *token = NULL;
	int i = 0, letters = 0;

	ignore = ignore;

	while ((*line)[i] && !is_delim((*line)[i], delims))
		letters += 1, i++;

	token = _realloc(token, 0, sizeof(*token) * letters + 1);
	if (token == NULL)
		return (NULL);

	_strncat(token, *line, letters);

	*line += letters;

	return (token);
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
	unsigned int words = 0, letters = 0, counter = 0;

	words = count_tokens(line, delims, ignore);
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
	command[counter] = NULL;
	return (command);
}

void print_parsed_line(char **command)
{
	int i;

	printf("Parsed line:\n");
	for (i = 0; command && command[i]; i++)
		printf("%s\n", command[i]);
}

/**
 * free_strs_array - Frees an array of strings.
 * @strs_array: The array of strings to be freed.
 */
void free_strs_array(char **strs_array)
{
	unsigned int counter;

	counter = 0;
	if (strs_array)
	{
		if (strs_array[counter])
			while (strs_array[counter] != NULL)
				free(strs_array[counter++]);
		free(strs_array);
	}
}
