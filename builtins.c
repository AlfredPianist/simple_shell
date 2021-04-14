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
 * @env: enviroment of the program
 * Return: -
*/
int help_builtin(__attribute__ ((__unused__)) char **commands,
		 __attribute__ ((__unused__)) char **env)
{
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
 * @env: enviroment of the program
 * Return: -
*/
int cd_builtin(__attribute__ ((__unused__)) char **commands,
	       __attribute__ ((__unused__)) char **env)
{
	return (1);
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
