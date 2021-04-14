#include "test.h"

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The difference of characters between strings. 0 if equal.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
		s1++, s2++;

	return (*s1 - *s2);
}

/**
 * _strdup - Duplicates a string allocating memory for it.
 * @str: The source string.
 *
 * Return: A duplication of the string.
 */
char *_strdup(char *str)
{
	char *dup = NULL;

	dup = _realloc(dup, 0, sizeof(*dup) * _strlen(str) + 1);
	if (dup == NULL)
		return (NULL);

	dup = _strcpy(dup, str);

	return (dup);
}

/**
 * add_node_alias - Adds an alias type node to any part of the list.
 * @head: The list's head.
 * @idx: The index in which the node will be added.
 * @var: The variable name to be added to the list.
 * @val: The value to be added to the list.
 *
 * Description: add_node_alias adds a node to any part of the list, be it at
 *              the beginning (idx = 0), at the end (idx = -1), or at
 *              any point in between. add_node_alias will not add a node if
 *              the index is larger than the list's length or if the index
 *              given is not valid.
 */
alias_t *add_node_alias(alias_t **head, int idx, char *var, char *val)
{
	alias_t *list, *node;

	list = *head, node = NULL;

	node = _realloc(node, 0, sizeof(*node));
	if (!node)
		return (NULL);

	node->name = _strdup(var), node->value = _strdup(val);

	if (*head == NULL)
	{
		node->next = NULL, *head = node;
		return (node);
	}
	if (idx == 0)
		node->next = *head, *head = node;
	else if (idx > 0)
	{
		while (list && 1 < idx--)
			if (list->next)
				list = list->next;
			else
			{
				free(node->name), free(node->value), free(node);
				return (NULL);
			}
		node->next = list->next, list->next = node;
	}
	else if (idx == -1)
	{
		while (list->next)
			list = list->next;
		node->next = NULL, list->next = node;
	}
	else
		free(node->name), free(node->value), free(node);
	return (node);
}

/**
 * print_list_alias - Prints the contents of an alias typed linked list.
 * @head: The list's head.
 */
void print_list_alias(alias_t *head)
{
	alias_t *list = head;
	char *string = NULL;

	while (list)
	{
		string = nstrcat(4, list->name, "='", list->value, "'\n");
		write(STDOUT_FILENO, string, _strlen(string) + 1);
		free(string);
		list = list->next;
	}
}

/**
 * free_list_alias - Frees an alias typed singly linked list.
 * @head: The list's head.
 */
void free_list_alias(alias_t **head)
{
	alias_t *next_node;

	if (head == NULL)
		return;

	next_node = (*head)->next;
	while (*head != NULL)
	{
		next_node = (*head)->next;
		free((*head)->name), free((*head)->value), free(*head);
		*head = next_node;
	}
	*head = NULL;
}

/**
 * parse_line - Parses a sentence into tokens.
 * @line: The input line stored.
 * @delims: The array of delimiters.
 * @ignore: The array of substring delimiters (matched pair).
 *
 * Return: The parsed sentence.
 */
void parse_line_alias(char *line, alias_t **alias)
{
	unsigned int letters = 0, counter = 0;
	char *name, *value;

	while (line && *line)
	{
		if (!is_delim(*line, " =\t\r\n"))
		{
			name = new_token(&line, " =\t\r\n");
			/* printf("name = %s\n", name); */
			/* free(name); */
			/* if (*line == '=' && *(line + 1) == '\'') */
			/* { */
			/* 	letters = is_substring(line + 1, "'"); */
			/* 	if (letters > 0) */
			/* 	{ */
			/* 		value = substring(line + 1, "'", letters); */
			/* 		add_node_alias(alias, counter, name, value); */
			/* 		free(name), free(value); */
			/* 		line += letters + 3; */
			/* 		counter++; */
			/* 	} */
			/* } */
			/* else */
			/* { */
			/* 	name = new_token(&line, " \t\r\n"); */
			/* 	/\* if (is_delim(*(line + 1), " \t\r\n")) *\/ */
			/* 	/\* 	print_alias_name(*alias, name); *\/ */
			/* } */
		}
		else if (*line == '=' && *(line + 1) == '\'')
		{
			letters = is_substring(line + 1, "'");
			if (letters > 0)
			{
				value = substring(line + 1, "'", letters);
				/* printf("value = %s\n", value); */
				/* add_node_alias(alias, counter, name, value); */
				free(name), free(value);
				line += letters + 3;
				counter++;
			}
		}
		else /* if (is_delim(*line, " \t\r\n") || *(line + 1) != '\0') */
		{
			printf("name = %s\n", name);
			/* print_alias_name(*alias, name); */
			/* if (value) */
			/* 	free(name); */
			printf("in else\n");
			line++;
		}
	}
}

int print_alias_name(alias_t *head, char *name)
{
	alias_t *list = head;
	char *string = NULL;

	while (list)
	{
		if (_strcmp(name, list->name) == 0)
		{
			string = nstrcat(4, list->name, "='", list->value, "'\n");
			write(STDOUT_FILENO, string, _strlen(string) + 1);
			free(string);
			return (0);
		}
		list = list->next;
	}

	string = nstrcat(3, "($): alias: ", name, ": not found\n");
	write(STDOUT_FILENO, string, _strlen(string) + 1);
	free(string);

	return (1);
}
