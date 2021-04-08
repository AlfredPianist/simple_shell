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

typedef struct builtin_s
{
	char *builtin_n;
	int (*builtin_f)(char **command);
} builtin_t;

/* Input */
int get_input_line(char **line);
char **parse_line(char **command, char *line, char del);

/* Process */
int select_exec(builtin_t *builtins, char **command);
int execute(char **command);

/* Memory management */
void free_all(char *line, char **command);

/* String manipulation */
int _strcmp(char *str1, char *str2);

/* Builtins */
int exit_builtin(char **commands);
int env_builtin(__attribute__ ((__unused__)) char **commands);
int setenv_builtin(__attribute__ ((__unused__)) char **commands);
int unsetenv_builtin(__attribute__ ((__unused__)) char **commands);
int help_builtin(__attribute__ ((__unused__)) char **commands);
int history_builtin(__attribute__ ((__unused__)) char **commands);
int cd_builtin(__attribute__ ((__unused__)) char **commands);
int alias_builtin(__attribute__ ((__unused__)) char **commands);

/* Misc */
void print_memory_hex(char *buffer, unsigned long int buffer_size);
void print_parse(char **command);

/* Environment */
void printenv(char **env);
int _setenv(char ***env, char *varN, char *varV);
char **copyEnv(char **env);

#endif
