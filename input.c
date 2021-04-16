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
 * pre_parse - Prepare line for the parse_line function (create commands)
 *             based on operator controls &&, ||, ; and comments (#)
 * @l: The line to be operated.
 * @controls: The operator controls list to add each operator control.
 *
 * Return: The list of commands.
 */
list_t *pre_parse(char *l, list_t **controls)
{
	int i = 0, k = 0;
	list_t *result = 0;
	char *string = 0;

	for (i = 0; l[i]; i++)
		if (_strncmp(l + i, "&&", 2) == 0 || _strncmp(l + i, "||", 2) == 0
			|| l[i] == ';' || l[i + 1] == 0 || _strncmp(l + i, " #", 2) == 0
			|| (l[i] == '#' && i == 0))
		{
			string = _realloc(0, 0, sizeof(char) * (i - k + 1));
			_strncat(string, l + k, i - k);
			k = l[i] == ';' ? i + 1 : i + 2;

			if (string && *string)
				add_node(&result, -1, string);

			if (_strncmp(l + i, "&&", 2) == 0)
				add_node(controls, -1, "&&");
			else if (_strncmp(l + i, "||", 2) == 0)
				add_node(controls, -1, "||");
			else if (l[i] == ';')
				add_node(controls, -1, ";");

			free(string);
			if (_strncmp(l + i, " #", 2) == 0 || (l[i] == '#' && i == 0))
				break;
		}
	add_node(controls, -1, ";");
	return (result);
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

	if (!command)
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
	if (command[0] == NULL)
	{
		free(command);
		return (NULL);
	}
	command[counter] = NULL;

	return (command);
}
