#include "header.h"

int select_exec(builtin_t *builtins, char **command, list_t **env)
{
	unsigned int i;
	struct stat stat_buff;
	unsigned int size_tmp;
	char *tmp = NULL, **path = NULL;

	for (i = 0; builtins[i].builtin_n != NULL; i++)
		if (strcmp(command[0], builtins[i].builtin_n) == 0)
			return (builtins[i].builtin_f(command, env));

	path = parse_line(path, get_env_var("PATH", *env), ':');

	for (i = 0; path[i]; i++)
	{
		size_tmp = strlen(command[0]) + strlen(path[i]) + 2;
		tmp = malloc(sizeof(char) * size_tmp);
		strcpy(tmp, path[i]);
		strcat(tmp, "/");
		strcat(tmp, command[0]);
		tmp[size_tmp - 1] = 0;
		if (stat(tmp, &stat_buff) == 0)
		{
			free(command[0]);
			free_all(0, path);
			command[0] = tmp;
			return (execute(command));
		}
		free(tmp);
	}

	free_all(0, path);

	if (stat(command[0], &stat_buff) == 0)
	{
		return (execute(command));
	}
	write(STDERR_FILENO, "archivo no encontrado\n", 22);
	return (-1);
}

/**
 * execute - Executes a command on a child process.
 * @command: The argument vector (parsed line).
 *
 * Return: 1 if successful.
 */
int execute(char **command)
{
	pid_t child_id;
	int status;

	child_id = fork();
	if (child_id == -1)
		/* Couldn't fork child process */
		perror(command[0]);
	else if (child_id == 0)
	{
		/* Child process */
		if (execve(command[0], command, NULL) == -1)
			perror(command[0]);
		/* Nota: liberar memoria aquí */
		/* exit(EXIT_FAILURE); */
	}
	else
	{
		/* Parent process */
		do {
			waitpid(child_id, &status, 0);
		} while (WIFEXITED(status) == FALSE && WIFSIGNALED(status) == FALSE);
	}
	return (1);
}
