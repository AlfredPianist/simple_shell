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
	ssize_t char_read = 0;
	int exec_status = 0, contador = 1, prev_exec = 0;
	list_t *env = copy_env(environment);
	alias_t *alias = NULL;
	builtin_t builtins[] = { {"exit", exit_builtin}, {"help", help_builtin},
				 {"env", env_builtin}, {"setenv", setenv_builtin},
				 {"unsetenv", unsetenv_builtin}, {NULL, NULL} },
		*f_built = 0;

	do {
		char_read = prompt_line(p, &line);

		if (char_read == EOF)
		{
			free(line);
			break;
		}

		command = parse_line(line, " \t\r\n", NULL), free(line);

		if (command)
		{
			f_built = select_bulit(builtins, command[0]);

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
/**
 * select_bulit - select the function requested by the user
 * @builtins: list of functions
 * @command_name: name of function requested
 * Return: function requested
 */
builtin_t *select_bulit(builtin_t *builtins, char *command_name)
{
	int i;

	for (i = 0; builtins[i].builtin_n != NULL; i++)
		if (_strcmp(command_name, builtins[i].builtin_n) == 0)
			return (&builtins[i]);
	return (&builtins[i]);
}
/**
 * prompt_line - display the prompt in line
 * @p:  prompt to display
 * @line: line to save the characters in input
 * Return: number of chars saved, -1 if is EOF
 */
int prompt_line(char *p, char **line)
{
	int char_read;

	/* Interactive mode */
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, p, _strlen(p));
		char_read = get_input_line(line);
	}
	/* Non-interactive mode */
	else
	{
		char_read = get_input_line(line);
		if (char_read == EOF)
			return (char_read);
	/*	write(STDOUT_FILENO, p, _strlen(p)); */
	}
	return (char_read);
}
