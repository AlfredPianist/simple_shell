#include "header.h"

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[])
{
	char *line;
	char **command;
	int exec_status;
	builtin_t builtins[] = { {"exit", exit_builtin}, {"help", help_builtin},
				 {"history", history_builtin}, {"env", env_builtin},
				 {"setenv", setenv_builtin}, {"unsetenv", unsetenv_builtin},
				 {"cd", cd_builtin}, {"alias", alias_builtin},
				 {NULL, NULL} };

	do {
		line = NULL;
		command = NULL;

		write(STDOUT_FILENO, "$ ", 3);

		line = get_input_line(line);
		command = parse_line(command, line);
		exec_status = select_exec(builtins, command);

		free_all(line, command);
	} while (exec_status == 0);

	exit(exec_status);
}

/*
 * PENDIENTES:
 * MAÑANA: PATH y env.
 * 1. Builtins env: advanced - (con argumentos), setenv, unsetenv, help,
 *    history, cd y alias.
 * 2. if (malloc == NULL).
 * 3. Manejo de errores adecuado, y exit codes.
 * 4. getline.
 * 6. Evitar Ctrl-C => SIGNALS.
 * 9. ; && y ||: ampliar parse para setear estas condiciones.
 * 10. alias.
 * 11. reemplazo de variables: $? y $$
 * 12. comentarios (#): ampliar parse para setear esta condición.
 * 15. input a script.
 */
