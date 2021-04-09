#include "header.h"

int select_exec(builtin_t *builtins, char **command)
{
	unsigned int i;

	if (command[0] == NULL)
		return (0);

	for (i = 0; builtins[i].builtin_n != NULL; i++)
		if (strcmp(command[0], builtins[i].builtin_n) == 0)
			return (builtins[i].builtin_f(command));

	return (execute(command));
}

char *which(char *PATH, char *command)
{
        struct stat stat_buff;

        stat(command, &stat_buff);

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

