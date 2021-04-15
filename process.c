#include "header.h"

/**
 * select_mode - select mode (interactive or non-interactive)
 * @p:  prompt to display
 * @line: line to save the characters in input
 * Return: number of chars saved, -1 if is EOF
 */
int select_mode(char *p, char **line)
{
	int char_read;

	/* Interactive mode */
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, p, _strlen(p));
		char_read = get_input_line(line);
	}
	/* Non-interactive mode */
	else
	{
		char_read = get_input_line(line);
		if (char_read == EOF)
			return (char_read);
	}
	return (char_read);
}

/**
 * select_built - select the function requested by the user
 * @builtins: list of functions
 * @command_name: name of function requested
 * Return: function requested
 */
builtin_t *select_built(builtin_t *builtins, char *command_name)
{
	int i;

	for (i = 0; builtins[i].builtin_n != NULL; i++)
		if (_strcmp(command_name, builtins[i].builtin_n) == 0)
			return (&builtins[i]);
	return (&builtins[i]);
}

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
	char *errorMsg, lineNoBuff[10];

	lineNo = lineNo;

	if (command[0] == 0)
		return (-1);

	path = parse_line(get_var("PATH", *env), ":\n", NULL);

	for (i = 0; path && path[i]; i++)
	{
		tmp = nstrcat(3, path[i], "/", command[0]);

		if (stat(tmp, &stat_buff) == 0 && access(tmp, F_OK | R_OK | X_OK) != -1)
		{
			free(command[0]), free_strs_array(path);
			command[0] = tmp;
			return (exec(command));
		}
		free(tmp);
	}

	free_strs_array(path);

	if (stat(command[0], &stat_buff) == 0 &&
		access(command[0], F_OK | R_OK | X_OK) != -1)
		return (exec(command));

	errorMsg = nstrcat(6, shellName, ": ", _itoa(10, 1, lineNo, lineNoBuff),
				": ", command[0], ": not found\n");
	write(STDERR_FILENO, errorMsg, _strlen(errorMsg));
	free(errorMsg);

	return (127);
}

/**
 * exec - Executes a command on a child process.
 * @command: The argument vector (parsed line).
 * Return: 1 if successful.
 */
int exec(char **command)
{
	pid_t child_id;
	int status, code = 0;

	child_id = fork();

	if (child_id == -1)
	{
		perror("Error");
		return (1);
	}
	else if (child_id == 0)
	{
		if (execve(command[0], command, NULL) == -1)
			exit(127);
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status))
			code = WEXITSTATUS(status);
	}
	return (code);
}
