#include "header.h"

int exit_caller(int prev_exec, char *shellName, int lineNo, char **command)
{
	int i = 0;
	char *error = NULL;
	char lineNoBuff[12];

	while (command[1] && command[1][i])
	{
		if (command[1][i] <= '0' && command[1][i] >= '9')
		{
			error = nstrcat(7, shellName, ": ", _itoa(12, 1, lineNo, lineNoBuff),
					": ", "Illegal number: ", command[1], "\n");
			return (2);
		}
		i++;
	}
	if (command[1])
		if (prev_exec != 0)
		exec_status = prev_exec;

	return (exec_status)
}
