#include "header.h"
#include <stdlib.h>

void interrup(__attribute__ ((__unused__)) int sign);

/**
 * prepare - print a string before the main execute
 */

void __attribute__ ((constructor)) prepare()
{
	signal(SIGINT, interrup);
}

/**
 * main - Entry point of the shell
 * @argc: number of arguments of the program
 * @argv: arguments of the program
 * @environment: -
 * Return: status of the program
 */
int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[],
	 __attribute__ ((__unused__))char **environment)
{
	char *line = NULL, **command, p[] = "#cisfun$ ";
	int char_read = 0, exec_status = 0, contador = 1, prev_exec = 0;
	list_t *env = copy_env(environment);
	alias_t *alias = NULL;
	builtin_t builtins[] = { {"exit", exit_builtin}, {"help", help_builtin},
				 {"env", env_builtin}, {"setenv", setenv_builtin},
				 {"unsetenv", unsetenv_builtin}, {"cd", cd_builtin},
				 {NULL, NULL} }, *f_built = 0;

	do {
		char_read = select_mode(p, &line);
		if (char_read == EOF)
		{
			free(line);
			break;
		}

		command = parse_line(line, " \t\r\n", NULL), free(line);
		if (command)
		{
			f_built = select_built(builtins, command[0]);
			prev_exec = (f_built->builtin_n != NULL) ?
				f_built->builtin_f(command, &alias, &env) :
				select_exec(command, &env, argv[0], contador);
			free_strs_array(command);

			if (f_built->builtin_n &&
				_strcmp(builtins[0].builtin_n, f_built->builtin_n) == 0)
				break;

			exec_status = prev_exec;
		}
		contador++;
	} while (char_read != EOF);

	if (env)
		free_list(&env);

	return (exec_status);
}

/**
 * interrup - function to control the SIGNAL_INT
 * @sign: signal
 */
void interrup(__attribute__ ((__unused__)) int sign)
{
	write(STDIN_FILENO, "\n#cisfun$ ", 10);
}
