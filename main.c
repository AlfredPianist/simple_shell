#include "header.h"
#include <stdlib.h>

builtin_t *select_bulit(builtin_t *builtins, char *command_name);
int prompt_line(char *p, char **line);

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[],
	char **environment)
{
	char *line = NULL, **command, p[] = "#cisfun$ ";
	ssize_t char_read = 0;
	int exec_status = 0, contador = 0;
	list_t *env = copy_env(environment);
	alias_t *alias = NULL;
	builtin_t builtins[] = { {"exit", exit_builtin},/*{"help", help_builtin}, */
	/*	{"history", history_builtin}, */ {"env", env_builtin},
		{"setenv", setenv_builtin}, {"unsetenv", unsetenv_builtin},
	/*	{"cd", cd_builtin}, {"alias", alias_builtin}, */
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
				f_built->builtin_f(command, &alias, &env):
				select_exec(command, &env, argv[0], contador);

			contador++;
			free_strs_array(command);
		}
	} while (char_read != EOF &&
		!(f_built->builtin_n && _strcmp(builtins[0].builtin_n, f_built->builtin_n) == 0));

	free_list(&env);
	exit(exec_status);
}

builtin_t *select_bulit(builtin_t *builtins, char *command_name)
{
	int i;

	for (i = 0; builtins[i].builtin_n != NULL; i++)
		if (_strcmp(command_name, builtins[i].builtin_n) == 0)
			return (&builtins[i]);
	return (&builtins[i]);
}

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

/*
 * PENDIENTES:
 * MAÑANA: PATH y env.
 * 1. Builtins env: advanced - (con argumentos), setenv, unsetenv, help,
 *    history, cd y alias.
 * 2. if (malloc == NULL).
 * 3. Manejo de errores adecuado, y exit codes.
]* 4. getline.
 * 6. Evitar Ctrl-C => SIGNALS.
 * 9. ; && y ||: ampliar parse para setear estas condiciones.
 * 10. alias.
 * 11. reemplazo de variables: $? y $$
 * 12. comentarios (#): ampliar parse para setear esta condición.
 * 15. input a script.
 */
