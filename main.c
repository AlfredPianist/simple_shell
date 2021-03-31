#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

char *get_input_line(char *line)
{
	scanf("%s", line);
	return (line);	
}

char **parsing_line(char **line)
{
	return (line);
}

int execute(char **command)
{
	printf("exec: %s\n", *command);
	return (1);
}


int main(int argc, char *argv[])
{
	char *line, **command;
	int result;

	line = malloc(sizeof(char) * 20);

	while (1)
	{
		//write(STDOUT_FILENO, "$ ", 3);
		printf("$ ");

		line = get_input_line(line);

		if (*line == EOF || strcmp(line, "exit") == 0)
			break;

		command = parsing_line(&line);
		result = execute(command);

		if (!result)
			printf("Error ocurred");
	}

	free(line);
	return (0);
}
