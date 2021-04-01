#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 20

char *get_input_line()
{
/*
 * Falta implementar el Ctrl-D, leer sobre signals,
 * retornar cantidad de letras y mapear "nada" a 0 y retorna -1.
*/
	char *line, tmp[BUFFER + 1];
	ssize_t char_read;
	int i, i_tmp;

	i = i_tmp = 1;
	line = NULL;
	char_read = BUFFER;

	while (char_read % BUFFER == 0)
	{
		for (i_tmp = 0; i_tmp < BUFFER + 1; i_tmp++)
			tmp[i_tmp] = '\0';
		char_read = read(STDIN_FILENO, tmp, BUFFER);

		line = realloc(line, sizeof(*line) * BUFFER * i++);
		strcat(line, tmp);
	}
	return (line);
}

char **parsing_line(char **line)
{
	return ({"/bin/ls", "-l", "/usr/", NULL});
}

int execute(char **command)
{
	if (execve(*command, command, NULL) == -1)
	{
		perror("Error:");
	}
}


int main(int argc, char *argv[])
{
	/** Pendiente, pasar como argv el comando **/
	char *line = NULL, **command;
	int result, i;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 3);

		line = get_input_line();

		if (*line == EOF || strcmp(line, "exit\n") == 0)
			break;

		command = parsing_line(&line);
		result = execute(command);

		if (!result)
			printf("Error ocurred");
	}

	free(line);
	return (0);
}

/* int main(void) */
/* 	{ */
/* 		char *line = NULL; */
/* 		size_t len = 0; */
/* 		ssize_t read; */

/* 		while ((read = getline(&line, &len, stdin)) != -1) { */
/* 			printf("Retrieved line of length %zu :", read); */
/* 			printf("%s\n", line); */
/* 		} */
/* 		printf("Retrieved line of length %ld :", read); */
/* 		printf("%x\n", line[0]); */

/* 		free(line); */
/* 		return (0); */
/* 	} */
