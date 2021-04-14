#include "header.h"

/**
 * select_exec - find and execute a file in or not int path
 * @command: command to execute
 * @env: list of enviroment vars
 * @shellName: name of the program
 * @lineNo: number of lines geted
 * Return: status of the execute
 */

int select_exec(char **command, list_t **env, char *shellName, int lineNo)
{
	unsigned int i;
	struct stat stat_buff;
	char *tmp = NULL, **path = NULL;
/*	char *errorMsg, lineNoBuff[10];*/
	lineNo = lineNo;
	
	if (command[0] == 0)
		return (-1);

	path = parse_line(get_var("PATH", *env), ":\n", NULL);

	for (i = 0; path[i]; i++)
	{
		tmp = nstrcat(3, path[i], "/", command[0]);

		if (stat(tmp, &stat_buff) == 0)
		{
			free(command[0]), free_strs_array(path);
			command[0] = tmp;
			return (execute(command, shellName));
		}
		free(tmp);
	}

	free_strs_array(path);

/*	if (stat(command[0], &stat_buff) == 0) */
	return (execute(command, shellName));
/*
	errorMsg = nstrcat(6, shellName, ": ", _itoa(10, 1, lineNo, lineNoBuff),
				": ", command[0], " not found\n");
	write(STDERR_FILENO, errorMsg, _strlen(errorMsg));
	free(errorMsg);
	return (-1);*/
}

/**
 * execute - Executes a command on a child process.
 * @command: The argument vector (parsed line).
 *
 * Return: 1 if successful.
 */
int execute(char **command, char * shellName)
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
			perror(shellName);
		/* Nota: liberar memoria aquí */
		/* exit(EXIT_FAILURE); */
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
