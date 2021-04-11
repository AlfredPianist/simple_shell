#include "header.h"

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[],
	char **environment)
{
	char *line = NULL, **command = NULL, p[]= "($) ";
	ssize_t char_read = 0;
	struct stat stat_buff;
	int exec_status = 0;
	list_t *env = NULL;
	builtin_t builtins[] = {
	/*	{"exit", exit_builtin}, {"help", help_builtin}, */
	/*	{"history", history_builtin}, */
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
	/*	{"cd", cd_builtin}, {"alias", alias_builtin}, */
		{NULL, NULL} };

	env = copy_env(environment);

	do {
		char_read = prompt_line(p, &line);
		if (char_read == EOF)
                {
                        free(line);
                        break;
                }
		command = parse_line(command, line, ' ');
		exec_status = select_exec(builtins, command, &env);
		free_all(line, command);
	} while (char_read != EOF);

	free_list(&env);
	exit(exec_status);
}

int prompt_line(char *p, char **line)
{
        int char_read;

       /* Interactive mode */
        if (isatty(STDIN_FILENO))
        {
                write(STDOUT_FILENO, p, _strlen(p));
                char_read = get_input_line(line);
		return (char_read);
                
        }
        /* Non-interactive mode */
        else
        {
                char_read = get_input_line(line);
		if (char_read == EOF)
			return (char_read);
                write(STDOUT_FILENO, p, _strlen(p));
        }
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
