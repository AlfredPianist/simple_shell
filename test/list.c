#include "test_list.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p_realloc;
	unsigned int counter;

	p_realloc = NULL;
	counter = 0;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
			return (NULL);
		while (counter < new_size)
			((char *) ptr)[counter++] = '\0';
		return (ptr);
	}

	p_realloc = malloc(new_size);
	if (p_realloc == NULL)
		return (NULL);

	for (counter = 0; counter < old_size && counter < new_size; counter++)
		((char *) p_realloc)[counter] = ((char *) ptr)[counter];

	if (new_size > old_size)
		while (counter < new_size)
			((char *) p_realloc)[counter++] = '\0';

	free(ptr);

	return (p_realloc);
}

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
 *              given is not valid.
 */
list_t *add_node(list_t **head, int idx, char *s)
{
	list_t *list, *node;

	list = *head, node = NULL;

	node = _realloc(node, 0, sizeof(*node));
	if (!node)
		return (NULL);

	node->str = NULL;
	node->str = _realloc(node->str, 0, sizeof(*(node->str)) * strlen(s) + 1);
	node->str = strcpy(node->str, s);

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
	list_t *list;

	list = head;

	if (head == NULL)
		printf("NULL\n");

	while (list)
		printf("%s\n", list->str), list = list->next;
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
		free((*head)->str);
		free(*head);
		*head = next_node;
	}
	*head = NULL;
}
