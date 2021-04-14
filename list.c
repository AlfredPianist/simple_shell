#include "header.h"

/**
 * add_node - Adds a node to any part of the list.
 * @head: The list's head.
 * @idx: The index in which the node will be added.
 * @s: The string to be added to the index.
 *
 * Description: add_node adds a node to any part of the list, be it at
 *              the beginning (idx = 0), at the end (idx = -1), or at
 *              any point in between. add_node will not add a node if
 *              the index is larger than the list's length or if the index
 *              given is not valid
 * Return: direction of the new node.
 */
list_t *add_node(list_t **head, int idx, char *s)
{
	list_t *list, *node;

	list = *head, node = NULL;

	node = _realloc(node, 0, sizeof(*node));
	if (!node)
		return (NULL);

	node->str = _strdup(s);

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
				free(node->str), free(node);
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
		free(node->str), free(node);
	return (node);
}

/**
 * print_list - Prints the contents of a linked list.
 * @head: The list's head.
 */
void print_list(list_t *head)
{
	list_t *list = head;
	char *string = NULL;

	while (list)
	{
		string = nstrcat(2, list->str, "\n");
		write(STDOUT_FILENO, string, _strlen(string) + 1);
		free(string);
		list = list->next;
	}
}

/**
 * delete_node_at_index - Deletes a node at the given index of the list.
 * @head: The list's head.
 * @index: The index of the node to be deleted.
 * Return: 1 if succeeded, -1 if failed
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int i_count;
	list_t *current_node, *tmp;

	i_count = 0;
	current_node = *head;

	if (current_node == NULL)
		return (-1);

	if (index == 0)
	{
		current_node = (*head)->next;
		free((*head)->str), free(*head);
		*head = current_node;
	}
	else
	{
		while (i_count < index - 1)
		{
			if (current_node == NULL)
				return (-1);
			current_node = current_node->next;
			i_count++;
		}
		tmp = current_node->next;
		current_node->next = tmp->next;
		free(tmp->str), free(tmp);
	}

	return (1);
}

/**
 * free_list- Frees a singly linked list.
 * @head: The list's head.
 */
void free_list(list_t **head)
{
	list_t *next_node;

	if (head == NULL)
		return;

	next_node = (*head)->next;
	while (*head != NULL)
	{
		next_node = (*head)->next;
		free((*head)->str), free(*head);
		*head = next_node;
	}
	*head = NULL;
}
