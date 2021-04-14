#include "header.h"

/**
 * get_var - Gets the value from a list's variable.
 * @var: Variable to find in env.
 * @list: The singly-linked list.
 *
 * Return: Value of the variable found in env, otherwise NULL.
 */
char *get_var(char *var, list_t *list)
{
	int i;
	list_t *curr_node;

	curr_node = list;
	for (i = 0; curr_node; i++)
	{
		if (_strncmp(curr_node->str, var, _strlen(var)) == 0)
			return (curr_node->str + _strlen(var) + 1);
		curr_node = curr_node->next;
	}

	return (NULL);
}

/**
 * add_to_list - Adds a new variable to the list. If it exists, it will
 *               replace its value.
 * @list: The list.
 * @varN: The variable's name.
 * @varV: The variable's value.
 *
 * Return: 1 if success, otherwise 0.
 */
int add_to_list(list_t **list, char *varN, char *varV)
{
	char *buff = NULL;
	list_t *curr_node;

	buff = nstrcat(3, varN, "=", varV);

	for (curr_node = *list; curr_node; curr_node = curr_node->next)
		if (_strncmp(curr_node->str, varN, _strlen(varN)) == 0)
		{
			free(curr_node->str);
			curr_node->str = buff;
			return (1);
		}

	add_node(list, -1, buff);
	free(buff);

	return (1);
}

/**
 * del_from_list - Clears a variable from the list.
 * @list: The list.
 * @varN: The variable's name.
 * Return: 1 if success, otherwise 0
 */
int del_from_list(list_t **list, char *varN)
{
	list_t *curr_node;
	unsigned int i;

	for (i = 0, curr_node = *list; curr_node; i++, curr_node = curr_node->next)
		if (_strncmp(curr_node->str, varN, _strlen(varN)) == 0)
		{
			delete_node_at_index(list, i);
			return (1);
		}
	return (0);
}

/**
 * copy_env - Creates a copy of the env passed to main.
 * @env: The environment.
 *
 * Return: Copy of the env as a singly-linked list, otherwise NULL.
 */
list_t *copy_env(char **env)
{
	unsigned int i;
	list_t *env_list;

	env_list = NULL;
	for (i = 0; env[i]; i++)
		add_node(&env_list, i, env[i]);

	return (env_list);
}
