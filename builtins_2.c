#include "header.h"

int env_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}

int setenv_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}

int unsetenv_builtin(__attribute__ ((__unused__)) char **commands)
{
	return (1);
}
