#include "header.h"

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
 * Return: direction of the new node
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
