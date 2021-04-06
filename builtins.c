#include "header.h"

int exit_builtin(char **commands)
{
	if (commands[1] != NULL)
	{
		/* Verificar si se introdujo un número */
		return (atoi(commands[1]));
	}
	return (1);
}

int help_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}

int history_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}

int cd_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}

int alias_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}
