#include "header.h"

/**
 * exit_builtin - close shell
 * @commands: command exit and his params
 * Return: status of the exit
*/
int exit_builtin(__attribute__ ((__unused__)) char **commands,
		 __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1] != NULL)
	{
		/* Verificar si se introdujo un número */
		return (_atoi(commands[1]));
	}
	return (1);
}
/**
 * help_builtin - display the help file of a command
 * @commands: command help and his params
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
 * Return: -
*/
int alias_builtin(__attribute__ ((__unused__)) char **commands,
		  __attribute__ ((__unused__)) char **env)
{
	return (1);
}
