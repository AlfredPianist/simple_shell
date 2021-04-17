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
 * execute_commands_line - parse and execute commands taken from get_line..
 * @status: The exit code from each function.
 * @line: The line of commands to be parsed.
 * @exit_called: A sentinel of the exit command.
 * @env: The environment list.
 * @alias: The alias list.
 * @shellName: The name of the shell.
 * @lineNo: The line number.
 *
 * Return: The exec_status of the called function
 */
int execute_commands_line(int status, char *line, int *exit_called,
		list_t **env, alias_t **alias, char *shellName, int lineNo)
{
	list_t *head_op = NULL, *head_cm = NULL,
		*commands = NULL, *op_controls = NULL;
	int exec_status = status, prev_exec = 0;
	builtin_t builtins[] = { {"exit", exit_builtin}, {"help", help_builtin},
				 {"env", env_builtin}, {"setenv", setenv_builtin},
				 {"unsetenv", unsetenv_builtin}, {"cd", cd_builtin},
				 {NULL, NULL} }, *f_built = 0;
	char **command = 0;

	commands = pre_parse(line, &op_controls);
	head_op = op_controls, head_cm = commands;
	if (commands)
	{
		do {
			command = parse_line(commands->str, " \t\r\n", NULL);
			if (command)
			{
				f_built = select_built(builtins, command[0]);
				prev_exec = (f_built->builtin_n != NULL) ?
					f_built->builtin_f(command, alias, env) :
					select_exec(command, env, shellName, lineNo);
				if (f_built->builtin_n &&
				    _strcmp(builtins[0].builtin_n, f_built->builtin_n) == 0)
				{
					if (prev_exec != 0)
						exec_status = prev_exec;
					*exit_called = 1;
					break;
				}
				exec_status = prev_exec, free_strs_array(command);
			}
			if ((_strncmp(op_controls->str, "&&", 2) == 0 && exec_status != 0) ||
			    (_strncmp(op_controls->str, "||", 2) == 0 && exec_status == 0))
				break;
		} while ((commands = commands->next) && (op_controls = op_controls->next));
		free_list(&head_cm);
	}
	free_list(&head_op);
	return (exec_status);
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

	for (i = 0; path && path[i] && command[0][0] != '/'
		    && command[0][0] != '.' ; i++)
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
		access(command[0], F_OK | R_OK | X_OK) != -1 &&
		(command[0][0] == '.' || command[0][0] == '/'))
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
