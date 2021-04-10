#include "header.h"

/**
 * env_builtin - prints the environment variables.
 * @commands:
 * Return:
 */
int env_builtin(__attribute__ ((__unused__)) char **commands,
		__attribute__ ((__unused__)) list_t **env)
{
	print_list(*env);
	return (1);
}

/**
 * setenv_builtin - create a new variable in environment from shell
 * @commands: command setenv and his params
 * Return: -
 */
int setenv_builtin(__attribute__ ((__unused__)) char **commands,
		   __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1] && commands[2])
	{
		_setenv(env, commands[1], commands[2]);
		return (1);
	}
	return (0);
}

/**
 * unsetenv_builtin - delete a variable in environment from shell
 * @commands: command setenv and his params
 * Return: -
 */
int unsetenv_builtin(__attribute__ ((__unused__)) char **commands,
		     __attribute__ ((__unused__)) list_t **env)
{
	if (commands[1])
	{
		_unsetenv(env, commands[1]);
		return (1);
	}
	return (1);
}
