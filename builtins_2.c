#include "header.h"

/**
 * env_builtin - prints the environment variables.
 * @commands: command exit and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: always 1
 */
int env_builtin(__attribute__ ((__unused__)) char **commands,
		__attribute__ ((__unused__)) alias_t **alias,
		__attribute__ ((__unused__)) list_t **env)
{
	if (*env)
	{
		print_list(*env);
		return (0);
	}
	return (1);
}

/**
 * setenv_builtin - create a new variable in environment from shell
 * @commands: command setenv and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: -
 */
int setenv_builtin(__attribute__ ((__unused__)) char **commands,
		   __attribute__ ((__unused__)) alias_t **alias,
		   __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1] && commands[2])
	{
		add_to_list(env, commands[1], commands[2]);
		return (1);
	}
	return (0);
}

/**
 * unsetenv_builtin - delete a variable in environment from shell
 * @commands: command setenv and his params
 * @alias: list of alias
 * @env: enviroment of the program
 * Return: -
 */
int unsetenv_builtin(__attribute__ ((__unused__)) char **commands,
		     __attribute__ ((__unused__)) alias_t **alias,
		     __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1])
	{
		del_from_list(env, commands[1]);
		return (1);
	}
	return (1);
}
