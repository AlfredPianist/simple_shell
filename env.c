#include "header.h"

/**
 * copyEnv - create a copy of a double pointer var
 * @env: pointer to copy
 * Return: copy of the env, otherwise 0
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

/**
 * getEnvVar - Gets the value of an env variable.
 * @var: Var to find in env.
 * @env: The env singly-linked list.
 * Return: value of the var found in env, otherwise NULL.
 */
char *get_env_var(char *var, list_t *env)
{
	int i;
	list_t *curr_node;

	curr_node = env;
	for (i = 0; curr_node; i++)
	{
		if (_strncmp(curr_node->str, var, _strlen(var)) == 0)
			return (curr_node->str + _strlen(var) + 1);
		curr_node = curr_node->next;
	}

	return (NULL);
}

/**
 * _setenv - Creates a new variable in the environment list.
 * @env: The environment list.
 * @varN: The variable's name.
 * @varV: The variable's value.
 *
 * Return: 1 if success, otherwise 0
 */
int _setenv(list_t **env, char *varN, char *varV)
{
	char *buff = NULL;
	list_t *curr_node;

	buff = nstrcat(3, varN, "=", varV);

	for (curr_node = *env; curr_node; curr_node = curr_node->next)
		if (_strncmp(curr_node->str, varN, _strlen(varN)) == 0)
		{
			free(curr_node->str);
			curr_node->str = buff;
			return (1);
		}

	add_node(env, -1, buff);
	free(buff);

	return (1);
}

/**
 * _unsetenv - clears a variable from the environment list.
 * @env: The environment list.
 * @varN: The variable's name.
 * @varV: The variable's value.
 *
 * Return: 1 if success, otherwise 0
 */
int _unsetenv(list_t **env, char *varN)
{
	list_t *curr_node;
	unsigned int i;

	for (i = 0, curr_node = *env; curr_node; i++, curr_node = curr_node->next)
		if (_strncmp(curr_node->str, varN, _strlen(varN)) == 0)
		{
			delete_node_at_index(env, i);
			return (1);
		}
	return (0);
}
