#include "header.h"

/**
 * env_builtin - 
 * @commands:
 * Return:
 */
int env_builtin(__attribute__ ((__unused__)) char **commands, char *** env)
{
	printenv(*env);
	return (1);
}
/**
 * setenv_builtin - create a new variable in environment from shell
 * @commands: command setenv and his params
 * Return: -
 */
int setenv_builtin(__attribute__ ((__unused__)) char **commands, __attribute__ ((__unused__)) char ***env)
{
	if (commands[1] && commands[2]) 
		_setenv(env, commands[1], commands[2]);
	return (1);
}
/**
 * unsetenv_builtin - delete a variable in environment from shell
 * @commands: command setenv and his params
 * Return: -
 */
int unsetenv_builtin(__attribute__ ((__unused__)) char **commands, __attribute__ ((__unused__)) char **env)
{
	return (1);
}
