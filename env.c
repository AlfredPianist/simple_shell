#include "header.h"

/**
 * copyEnv - create a copy of a double pointer var
 * @env: pointer to copy
 * Return: copy of the env, otherwise 0
 */
list_t *copy_env(char **env)
{
	unsigned int i = 0, j = 0;
	list_t *env_list;

	if (!env_list)
		return (0);

	for (i = 0; env[i]; i++)
		add_node(&env_list, env[i], i);

	return (env_list);
}

void add_node(list_t **head, int idx, char *s)
{
	list_t *list, *node;

	list = *head;

	node = malloc(sizeof(*node));
	if (!node)
		return;

	node->str = _realloc(node->str, 0, sizeof(node->str) * strlen(s) + 1);
	if (!node->str)
		return;
	/* Check malloc */
	strcpy(node->str, s);

	if (*head == NULL)
	{
		node->next = NULL, *head = node;
		return;
	}

	if (idx == 0)
	{
		node->next = *head, *head = node;
		return;
	}

	if (idx > 0)
		while (list && 1 < idx--)
			if (list->next)
				list = list->next;
			else
				return;

	if (idx == -1)
		while (list)
			list = list->next;

	node->next = list->next, list->next = node;
}
/**
 * _setenv - create a new var in a in a double pointer environment
 * @env: direction of the double pointer env to modify
 * @varN: pointer var to modify or create in env
 * @varV: value of the pointer var to modify or create
 * Return: 1 if success, otherwise 0
 */
int _setenv(char ***env, char *varN, char *varV)
{
	int i;
	int buff_size = strlen(varN) + strlen(varV) + 2;
	char *buff = malloc(sizeof(*buff) * buff_size);

	strcat(buff, varN);
	strcat(buff, "=");
	strcat(buff, varV);
	buff[buff_size - 1] = '\0';

	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (strncmp((*env)[i], varN, strlen(varN)) == 0)
		{
			(*env)[i] = buff;
			return (1);
		}
	}
	*env = realloc(*env, sizeof(**env) * (i + 2));
	(*env)[i] = buff;
	(*env)[i + 1] = NULL;

	return (1);
}
/**
 * getEnvVar - get the vallue of a pointer var in double pointer env
 * @var: var to find in env
 * @env: double pointer environment to check
 * Return: value of the var finded in env, otherwise 0
 */
char *getEnvVar(char *var, char **env)
{
        int i = 0;

        for (i = 0; env && env[i]; i++)
		if (strncmp(env[i], var, strlen(var)) == 0)
			return (env[i] + strlen(var) + 1);

	return (0);
}

void printenv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}
