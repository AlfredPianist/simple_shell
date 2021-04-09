#include "header.h"

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[],
	char **environment)
{
	char *line = NULL, **command = NULL, **path;
	ssize_t char_read = 0, i;
	struct stat stat_buff;
	int exec_status = 0;
	list_s env;

	builtin_t builtins[] = {
	/*	{"exit", exit_builtin}, {"help", help_builtin}, */
	/*	{"history", history_builtin}, */
		{"env", env_builtin}, 
		{"setenv", setenv_builtin},
	/*	{"unsetenv", unsetenv_builtin},*/
	/*	{"cd", cd_builtin}, {"alias", alias_builtin}, */
		{NULL, NULL} };

	env = copyEnv(environment);

	do {
		/* Interactive mode */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "($) ", 5);
			char_read = get_input_line(&line);
			if (char_read == EOF)
			{
				free(line);
				break;
			}
		}
		/* Non-interactive mode */
		else
		{
			char_read = get_input_line(&line);
			if (char_read == EOF)
			{
				free(line);
				break;
			}
			write(STDOUT_FILENO, "($) ", 5);
		}
		command = parse_line(command, line, ' ');
       	        exec_status = select_exec(builtins, command, env);
                free_all(line, command);
	} while (char_read != EOF);

	free_all(NULL, env);
	exit(exec_status);
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
