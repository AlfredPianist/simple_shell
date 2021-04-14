#include "header.h"
#include <stdlib.h>

builtin_t *select_bulit(builtin_t *builtins, char *command_name);
int prompt_line(char *p, char **line);

/**
 * main - Entry point of the shell
 * @argc: number of arguments of the program
 * @argv: arguments of the program
 * @environment: -
 * Return: status of the program
 */
int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[],
	char **environment)
{
	char *line = NULL, **command, p[] = "#cisfun$ ";
	ssize_t char_read = 0;
	int exec_status = 0, contador = 0;
	list_t *env = copy_env(environment);
	alias_t *alias = NULL;
	builtin_t builtins[] = { {"exit", exit_builtin},
		{"env", env_builtin},
		{"setenv", setenv_builtin}, {"unsetenv", unsetenv_builtin},
		{NULL, NULL} }, *f_built = 0;

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

			exec_status = (f_built->builtin_n != NULL) ?
				f_built->builtin_f(command, &alias, &env) :
				select_exec(command, &env, argv[0], contador);

			contador++;
			free_strs_array(command);
		}
	} while (char_read != EOF &&
		!(f_built->builtin_n &&
			_strcmp(builtins[0].builtin_n, f_built->builtin_n) == 0));

	free_list(&env);
	exec_status = 0;
	return (exec_status);
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
		write(STDOUT_FILENO, p, _strlen(p));
	}
	return (char_read);
}
