#include "header.h"
#include <stdlib.h>

void interrup(__attribute__ ((__unused__)) int sign);
list_t *pre_parse(char *, list_t **);
int execute_commands_line(int status, char *line, int *exit_called,
			  list_t **env, alias_t **alias, char *shellName, int lineNo);
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
	 __attribute__ ((__unused__)) char *argv[], char **environment)
{
	char *line = NULL, p[] = "#cisfun$ ";
	int char_read = 0, status = 0, contador = 1, exit_called = 0;
	list_t *env = copy_env(environment);
	alias_t *alias = NULL;

	line = getcwd(NULL, 0);
	if (line == NULL)
		perror("Error");
	else
		add_to_list(&env, "OLDPWD", line), free(line);

	do {
		char_read = select_mode(p, &line);
		if (char_read == EOF)
		{
			free(line);
			break;
		}
		status = execute_commands_line(status, line, &exit_called, &env,
					       &alias, argv[0], contador);
		free(line);

		contador++;
	} while (char_read != EOF && exit_called == 0);

	if (env)
		free_list(&env);

	return (status);
}

/**
 * interrup - function to control the SIGNAL_INT
 * @sign: signal
 */
void interrup(__attribute__ ((__unused__)) int sign)
{
	write(STDIN_FILENO, "\n#cisfun$ ", 10);
}
