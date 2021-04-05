#ifndef _SUPER_SIMPLE_SHELL_
#define _SUPER_SIMPLE_SHELL_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* Definition of booleans TRUE and FALSE */
#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

/**
 * enum boolean_e - Typedef of a boolean data type.
 * @FALSE: false.
 * @TRUE: true.
 */
typedef enum boolean_e
{
	FALSE,
	TRUE
} boolean;

typedef struct token_s
{
	char *token_str;
	struct token_s *next;
} token_t;

int main(__attribute__ ((__unused__)) int argc,
	 __attribute__ ((__unused__)) char *argv[]);

char *get_input_line(char *line);
char **parse_line(char **command, char *line);

#endif
