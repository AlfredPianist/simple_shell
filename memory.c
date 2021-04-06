#include "header.h"

/**
 * _realloc - reallocates memory depending on its new size and initializes
 *            new memory with zeroes.
 * @ptr: The array of memory originally allocated.
 * @old_size: The array's allocated old size.
 * @new_size: The array's new size to be allocated.
 *
 * Return: A pointer to the address if successful at allocating memory.
 *         Otherwise, returns NULL. NULL if new_size == 0.
 */
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

void free_all(char *line, char **command)
{
	unsigned int counter;

	counter = 0;
	while (command[counter] != NULL)
		free(command[counter++]);

	free(command);
	free(line);
}
