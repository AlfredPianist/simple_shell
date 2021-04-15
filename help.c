#include "header.h"

/**
 * help - The first batch of builtin help display prompts.
 * @command: The builtin to compare.
 *
 * Return: 0 if builtin exists.
 */
int help(char *command)
{
	char *help = NULL;

	if (_strcmp(command, "exit") == 0)
	{
		help = nstrcat(4, "Usage:\texit [n]\n",
			       "\tExit the shell.\n\n",
			       "\tExits the shell with a status of n. If n is omitted, the exit status\n",
			       "\tis that of the last command executed.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	else if (_strcmp(command, "help") == 0)
	{
		help = nstrcat(4, "Usage:\thelp [BUILTIN]\n",
			       "\tDisplay information about builtin commands.\n\n",
			       "\tDisplays a brief summary of command BUILTIN.\n",
			       "\tReturns success unless BUILTIN is not found.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	else if (_strcmp(command, "env") == 0)
	{
		help = nstrcat(3, "Usage:\tenv\n",
			       "\tPrints all the environment variables.\n\n",
			       "\tReturns success unless environment is not found.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	else if (_strcmp(command, "setenv") == 0)
	{
		help = nstrcat(3, "Usage:\tsetenv [VAR_NAME] [VAR_VALUE]\n",
			       "\tCreates a new variable in the environment.\n",
			       "If VAR_NAME already exists, VAR_VALUE will be overwritten\n\n",
			       "\tReturns success unless environment variable couldn't be set.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	return (help_2(command));
}

/**
 * help_2 - The second batch of builtin help display prompts.
 * @command: The builtin to compare.
 *
 * Return: 0 if builtin exists.
 */
int help_2(char *command)
{
	char *help = NULL;

	if (_strcmp(command, "unsetenv") == 0)
	{
		help = nstrcat(4, "Usage:\tunsetenv [VAR_NAME]\n",
			       "\tDeletes a variable from the environment.\n\n",
			       "\tReturns success unless variable couldn't be deleted or not found.\n",
			       "\tis that of the last command executed.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	else if (_strcmp(command, "history") == 0)
	{
		help = nstrcat(3, "Usage:\thistory\n",
			       "\tPrints all the environment variables.\n\n",
			       "\tReturns success unless environment is not found.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	else if (_strcmp(command, "cd") == 0)
	{
		help = nstrcat(3, "Usage:\tcd DIR_PATH\n",
			       "\tChanges the current directory to DIR_PATH\n\n",
			       "\tReturns success unless the directory couldn't be found.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	return (help_3(command));
}

/**
 * help_3 - The third batch of builtin help display prompts.
 * @command: The builtin to compare.
 *
 * Return: 0 if builtin exists, 1 otherwise.
 */
int help_3(char *command)
{
	char *help = NULL;

	if (_strcmp(command, "alias") == 0)
	{
		help = nstrcat(4, "Usage:\thelp [BUILTIN]\n",
			       "\tDisplay information about builtin commands.\n\n",
			       "\tDisplays a brief summary of command BUILTIN.\n",
			       "\tReturns success unless BUILTIN is not found.\n");
		write(STDOUT_FILENO, help, _strlen(help)), free(help);
		return (0);
	}
	help = _strdup("Error: Command not found.\n");
	write(STDERR_FILENO, help, _strlen(help)), free(help);

	return (1);
}
