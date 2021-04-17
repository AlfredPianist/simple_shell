#include "header.h"

/**
 * exit_builtin - close shell
 * @commands: command exit and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: status of the exit
*/
int exit_builtin(__attribute__ ((__unused__)) char **commands,
		 __attribute__ ((__unused__)) alias_t **alias,
		 __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1] != NULL)
		return (_atoi(commands[1]));

	return (0);
}

/**
 * help_builtin - display the help file of a command
 * @commands: command help and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: -
 */
int help_builtin(__attribute__ ((__unused__)) char **commands,
		 __attribute__ ((__unused__)) alias_t **alias,
		 __attribute__ ((__unused__)) list_t **env)
{
	char *help = NULL;

	if (commands[1])
	{
		if (_strcmp(commands[1], "exit") == 0)
		{
			help = nstrcat(4, "Usage:\texit [n]\n",
				       "\tExit the shell.\n\n",
				       "\tExits the shell with a status of n. If n is omitted, the exit status\n",
				       "\tis that of the last command executed.\n");
			write(STDOUT_FILENO, help, _strlen(help)), free(help);
			return (0);
		}
		else if (_strcmp(commands[1], "help") == 0)
		{
			help = nstrcat(4, "Usage:\thelp [BUILTIN]\n",
				       "\tDisplay information about builtin commands.\n\n",
				       "\tDisplays a brief summary of command BUILTIN.\n",
				       "\tReturns success unless BUILTIN is not found.\n");
			write(STDOUT_FILENO, help, _strlen(help)), free(help);
			return (0);
		}
		else if (_strcmp(commands[1], "env") == 0)
		{
			help = nstrcat(3, "Usage:\tenv\n",
				       "\tPrints all the environment variables.\n\n",
				       "\tReturns success unless environment is not found.\n");
			write(STDOUT_FILENO, help, _strlen(help)), free(help);
			return (0);
		}
		else
		{
			help = _strdup("Error: Command not found.\n");
			write(STDERR_FILENO, help, _strlen(help)), free(help);
		}
		return (1);
	}
	help = _strdup("Error: Command not specified.\nUsage: help [BUILTIN]\n");
	write(STDERR_FILENO, help, _strlen(help)), free(help);
	return (1);
}
/**
 * history_builtin - display the history file
 * @commands: command history and his params
 * @env: enviroment of the program
 * Return: -
*/
int history_builtin(__attribute__ ((__unused__)) char **commands,
		    __attribute__ ((__unused__)) char **env)
{
	return (1);
}
/**
 * cd_builtin - change the current directory of the shell
 * @commands: command cd and his params
 * @alias: The alias list
 * @env: enviroment of the program
 * Return: -
*/
int cd_builtin(char **commands,
	       __attribute__ ((__unused__)) alias_t **alias,
	       __attribute__ ((__unused__)) list_t **env)
{
	if (chdir(commands[1]) == -1)
	{
		perror("Error cd");
		return (-1);
	}
	return (0);
}
/**
 * alias_builtin - create an alias of a command
 * @commands: command alias and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: -
*/
int alias_builtin(__attribute__ ((__unused__)) char **commands,
		  __attribute__ ((__unused__)) alias_t **alias,
		  __attribute__ ((__unused__)) list_t **env)
{
	if (!commands[1])
		print_list_alias(*alias);

	return (1);
}
