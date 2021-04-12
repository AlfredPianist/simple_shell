#include "header.h"

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
