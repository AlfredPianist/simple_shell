#include "header.h"
#include <stdlib.h>

void interrup(__attribute__ ((__unused__)) int sign);
list_t *pre_parse(char *l, list_t **controls);
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
		status = execute_commands_line(status, line, &exit_called,
					       &env, &alias, argv[0], contador);
		free(line);

		contador++;
	} while (char_read != EOF && exit_called == 0);

	if (env)
		free_list(&env);

	return (status);
}

/**
 * execute_commands_line - Execute commands in a line.
 * @status: The process status.
 * @line: The input line to be processed.
 * @exit_called: The sentinel for exit if called.
 * @env: The environment list.
 * @alias: The alias list.
 * @shellName: The shellName.
 * @lineNo: The line number.
 *
 * Return: The last process status.
 */
int execute_commands_line(int status, char *line, int *exit_called,
			  list_t **env, alias_t **alias, char *shellName, int lineNo)
{
	list_t *head_op = NULL, *head_cm = NULL, *commands = NULL,
		*op_controls = NULL;
	int exec_status = status, prev_exec = 0;
	builtin_t builtins[] = { {"exit", exit_builtin}, {"help", help_builtin},
				 {"env", env_builtin}, {"setenv", setenv_builtin},
				 {"unsetenv", unsetenv_builtin}, {"cd", cd_builtin},
				 {NULL, NULL} }, *f_built = 0;
	char **command = 0;

	commands = pre_parse(line, &op_controls);
	head_op = op_controls, head_cm = commands;
	if (commands)
	{
		do {
			command = parse_line(commands->str, " \t\r\n", NULL);
			if (command)
			{
				f_built = select_built(builtins, command[0]);
				prev_exec = (f_built->builtin_n != NULL) ?
					f_built->builtin_f(command, alias, env) :
					select_exec(command, env, shellName, lineNo);
				free_strs_array(command);
				if (f_built->builtin_n &&
				    _strcmp(builtins[0].builtin_n, f_built->builtin_n) == 0)
				{
					if (prev_exec != 0)
						exec_status = prev_exec;
					*exit_called = 1;
					break;
				}
				exec_status = prev_exec;
			}
			if ((_strncmp(op_controls->str, "&&", 2) == 0 && exec_status != 0) ||
			    (_strncmp(op_controls->str, "||", 2) == 0 && exec_status == 0))
				break;
		} while ((commands = commands->next) && (op_controls = op_controls->next));
		free_list(&head_cm);
	}
	free_list(&head_op);
	return (exec_status);
}

/**
 * pre_parse - A previous check for the parser.
 * @l: The line to be passed.
 * @controls: The list of control operators (&&, || and ;).
 *
 * Return: The list of commands stripped of their control operators.
 */
list_t *pre_parse(char *l, list_t **controls)
{
	int i = 0, k = 0;
	list_t *result = 0;
	char *string = 0;

	for (i = 0; l[i]; i++)
		if (_strncmp(l + i, "&&", 2) == 0 || _strncmp(l + i, "||", 2) == 0
		    || l[i] == ';' || l[i + 1] == 0 || _strncmp(l + i, " #", 2) == 0
		    || (l[i] == '#' && i == 0))
		{
			string = _realloc(0, 0, sizeof(char) * (i - k + 1));
			_strncat(string, l + k, i - k);
			k = l[i] == ';' ? i + 1 : i + 2;

			if (string && *string)
				add_node(&result, -1, string);

			if (_strncmp(l + i, "&&", 2) == 0)
				add_node(controls, -1, "&&");
			else if (_strncmp(l + i, "||", 2) == 0)
				add_node(controls, -1, "||");
			else if (l[i] == ';')
				add_node(controls, -1, ";");

			free(string);
			if (_strncmp(l + i, " #", 2) == 0 || (l[i] == '#' && i == 0))
				break;
		}
	add_node(controls, -1, ";");
	return (result);
}

/**
 * interrup - function to control the SIGNAL_INT
 * @sign: signal
 */
void interrup(__attribute__ ((__unused__)) int sign)
{
	write(STDIN_FILENO, "\n#cisfun$ ", 10);
}
