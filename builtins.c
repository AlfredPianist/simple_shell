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
	char *err = NULL;

	if (commands[1])
		return (help(commands[1]));

	err = _strdup("Error: Command not specified.\nUsage: help [BUILTIN]\n");
	write(STDERR_FILENO, err, _strlen(err)), free(err);
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
 * @alias: the alias list.
 * @env: enviroment of the program
 * Return: -
*/
int cd_builtin(char **commands,
	       __attribute__ ((__unused__)) alias_t **alias,
	       __attribute__ ((__unused__)) list_t **env)
{
	char *oldwd = NULL, *cwd = NULL;

	if (_strcmp(commands[1], "-") == 0)
	{	oldwd = _strdup(get_var("OLDPWD", *env)), cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{	perror("Error");
			return (1);
		}
		else
			add_to_list(env, "OLDPWD", cwd), free(cwd), add_to_list(env, "PWD", oldwd);
		if (chdir(oldwd) == -1)
		{	perror("Error"), free(oldwd);
			return (1);
		}
		free(oldwd);
		return (0);
	}
	if (!commands[1])
		cwd = _strdup(get_var("HOME", *env));
	printf("When cd alone %s\n", cwd);
	oldwd = getcwd(NULL, 0);
	if (oldwd == NULL)
	{	perror("Error");
		return (1);
	}
	else
		add_to_list(env, "OLDPWD", oldwd), free(oldwd);
	if (chdir(commands[1]) == -1)
	{	perror("Error");
		return (-1);
	}
	if (commands[1])
	{	cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			perror("No dir");
		else
			add_to_list(env, "PWD", cwd), free(cwd);
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
