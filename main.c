#include "header.h"

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[])
{
	pid_t child_id;
	unsigned int counter;
	char *line;
	char **command;
	int status;

	counter = 0;
	line = NULL;
	command = NULL;

	line = get_input_line(line);
	command = parse_line(command, line);

	child_id = fork();
	if (child_id == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_id == 0)
	{
		/* printf("Ejecutando comando\n"); */
		if (execve(command[0], command, NULL) == -1)
			perror("Error");
	}
	else
		wait(&status); /* printf("Ejecutado, fin\n"); */

	/* FREEEEEEEE */
	counter = 0;
	while (command[counter] != NULL)
		free(command[counter]), counter += 1;
	free(line);
	free(command);

	exit(EXIT_SUCCESS);
}

/*
 * PENDIENTES:
 * 1. Builtin env, exit y PATH.
 * 2. if (malloc == NULL).
 * 3. Manejo de errores adecuado, y exit codes.
 * 4. getline
 * 5. arguments for exit.
 * 6. Evitar Ctrl-C => SIGNALS.
 * 7. setenv y unsetenv.
 * 8. cd
 * 9. ;, && y ||
 * 10. alias.
 * 11. reemplazo de variables: $? y $$
 * 12. comentarios (#).
 * 13. help builtin.
 * 14. history.
 * 15. input a script.
 */
