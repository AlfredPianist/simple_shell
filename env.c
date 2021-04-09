#include <unistd.h>
#include "header.h"

char **copyEnv(char **env)
{
	unsigned int i = 0, j = 0;
	char **newEnv;

	while (env[i])
		i++;

	newEnv = malloc(sizeof(*newEnv) * (i + 1));

	for (i = 0; env[i]; i++)
	{
		newEnv[i] = malloc(sizeof(*newEnv[i]) * (strlen(env[i]) + 1));
		strcpy(newEnv[i], env[i]);
		newEnv[i][strlen(env[i])] = '\0';
	}
	newEnv[i] = NULL;

	return (newEnv);
}

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

void printenv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
		printf("%s\n", env[i++]);
}
