#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printenv(char **env);
int _setenv(char ***env, char *varN, char *varV);
char **copyEnv(char **env);

int main(__attribute__ ((unused)) int ac,
	 __attribute__ ((unused)) char **av,
	 char **env_org)
{
	int i = 0;
	char **env;

	/* printf("copying env\n"); */
	env = copyEnv(env_org);
	/* printf("copied env\n"); */

	/* printf("printing original env\n"); */
	/* printenv(env); */
	/* printf("printing copied env\n"); */
	/* printenv(env_org); */
	/* printf("printed env\n"); */

	/* printf("setting new env variable\n"); */
	_setenv(&env, "NEWVAR1", "asdasdojieijoijowejiewrwer");
	/* printf("new variable set\n"); */

	/* printf("printing copied env with new variable\n"); */
	printenv(env);
	/* printf("printed copied env with new variable\n"); */

	/* printf("freeing copy env:\n"); */
	while (env[i])
		free(env[i]), i++;
	free(env);
	/* printf("freed copy env\n"); */

	return (0);
}

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
	char *buff = calloc(buff_size, sizeof(*buff));

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
