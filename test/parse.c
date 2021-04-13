#include "test.h"

/**
 * _strncat - Concatenates two strings.
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

/**
 * *_strpbrk - searches a string for any of a set of bytes.
 * @s: the source string.
 * @accept: the substring of accepted characters.
 *
 * Return: a pointer to the byte in s that matches one of the bytes in accept,
 *         or NULL if not found.
 */
char *_strpbrk(char *s, char *accept)
{
	unsigned int index_s, index_a;
	char *res = NULL;

	for (index_s = 0; s[index_s] != '\0' && res == NULL; index_s++)
	{
		for (index_a = 0; accept[index_a] != '\0'; index_a++)
		{
			if (s[index_s] == accept[index_a])
			{
				res = s + index_s;
				break;
			}
		}
	}

	return (res);
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
	int tokens = 0, i = 0, len_substring = 0;

	while (line && *line)
	{
		if (*line == '\'')
		{
			len_substring = is_substring(line, ignore);
			if (len_substring > 0)
				line += len_substring + 2;
			tokens += 1;
		}
		else
		{
			if ((!is_delim(*line, delims) && is_delim(*(line + 1), delims))
			    || (!is_delim(*line, delims) && !(*(line + 1))))
				tokens += 1;
			line++;
		}
	}

	return (tokens);
}

char *new_token(char **line, char *delims)
{
	char *token = NULL;
	int i = 0, letters = 0;

	while ((*line)[i] && !is_delim((*line)[i], delims))
		letters += 1, i++;

	token = _realloc(token, 0, sizeof(*token) * letters + 1);
	if (token == NULL)
		return (NULL);

	_strncat(token, *line, letters);

	*line += letters;

	return (token);
}

int is_substring(char *line, char *ignore)
{
	char *begin, *end;
	int i = 0;

	begin = end = NULL;
	if (!ignore && !*ignore)
		return (-1);

	begin = _strpbrk(line, ignore);
	if (begin == NULL || begin + 1 == '\0')
		return (-1);

	end = _strpbrk(begin + 1, ignore);
	if (end == NULL)
		return (-1);

	while (begin != end)
		begin++, i++;

	/* printf("len of substring = %d\n", i - 1), fflush(stdout); */
	return (i - 1);
}

char *substring(char *line, char *ignore, int len)
{
	char *begin, *substring;

	substring = begin = NULL;

	begin = _strpbrk(line, ignore) + 1;

	substring = _realloc(substring, 0, sizeof(*substring) * len + 1);
	_strncat(substring, begin, len);

	return (substring);
}

/**
 * parse_line - Parses a sentence into tokens, its delimiter being ' '
 * @command: The pointer to the array of strings of the future parsed sentence.
 * @line: The input line stored.
 *
 * Return: The parsed sentence.
 */
char **parse_line(char *line, char *delims, char *ignore)
{
	unsigned int words = 0, letters = 0, counter = 0;
	char **command = NULL;

	words = count_tokens(line, delims, ignore);
	printf("number of tokens = %d\n", words);
	command = _realloc(command, 0, sizeof(*command) * (words + 1));

	if (command == NULL)
		return (NULL);

	while (line && *line)
	{
		if (!is_delim(*line, delims))
		{
			if (*line == '\'')
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
