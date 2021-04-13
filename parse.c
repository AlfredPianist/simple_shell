#include "header.h"

/**
 * is_delim - Verifies if a given character is a delimiter.
 * @curr_char: The current char to be compared.
 * @delims: The array of delimiters.
 *
 * Return: 1 if is a delimiter, 0 otherwise.
 */
int is_delim(char curr_char, char *delims)
{
	while (delims && *delims)
		if (curr_char == *delims++)
			return (1);
	return (0);
}

/**
 * count_tokens - Counts the number of tokens given a set of delimiters
 *                and characters to be ignored.
 * @line: The line to be counted.
 * @delims: The array of delimiters.
 * @ignore: The array of characters acting as delimiters of a substring
 *
 * Return: The number of tokens counted.
 */
int count_tokens(char *line, char *delims, char *ignore)
{
	int tokens = 0, len_substring = 0;

	while (line && *line)
	{
		if (ignore && *line == *ignore)
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

/**
 * new_token - Creates a new token.
 * @line: The address of the current line (moves the pointer forward).
 * @delims: The array of delimiters.
 *
 * Return: the tokenized string, NULL otherwise.
 */
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

/**
 * is_substring - Verifies if a given array is a substring
 *                (delimited by a matched pair of characters).
 * @line: The line to be searched for substring.
 * @ignore: The array of characters acting as delimiters for the substring.
 *
 * Return: The length of the substring, -1 if substring doesn't exist.
 */
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

	return (i - 1);
}

/**
 * substring - Creates a substring token.
 * @line: The line to be searched.
 * @ignore: The array of substring delimiters.
 * @len: The length of the substring.
 *
 * Return: The created substring, NULL otherwise.
 */
char *substring(char *line, char *ignore, int len)
{
	char *begin, *substring;

	substring = begin = NULL;
	begin = _strpbrk(line, ignore) + 1;

	substring = _realloc(substring, 0, sizeof(*substring) * len + 1);
	if (substring == NULL)
		return (NULL);

	_strncat(substring, begin, len);

	return (substring);
}
