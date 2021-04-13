#ifndef _SUPER_SIMPLE_SHELL_
#define _SUPER_SIMPLE_SHELL_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

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

/**
 * struct list_s - A general purpose singly linked list structure.
 * @str: A string.
 * @next: The pointer to the next node.
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A structure for the diverse shell builtins.
 * @builtin_n: The name of the builtin.
 * @builtin_f: A function pointer to the builtin's function.
 */
typedef struct builtin_s
{
	char *builtin_n;
	int (*builtin_f)(char **command, list_t **alias, list_t **env);
} builtin_t;

/* Input */
int get_input_line(char **line);
char **parse_line(char **command, char *line, char *delims, char *ignore);
int is_delim(char curr_char, char *delims);
int count_tokens(char *line, char *delims, char *ignore);
char *new_token(char **line, char *delims, char *ignore);

/* Process */
int select_exec(char **command, list_t **env, char *, int);
int execute(char **command);

/* Memory management */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_strs_array(char **strs_array);

/* String manipulation */
int _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *nstrcat(const int tot_strs, ...);

/* Builtins */
int exit_builtin(char **commands, list_t **alias, list_t **env);
int env_builtin(char **commands, list_t **alias, list_t **env);
int setenv_builtin(char **commands, list_t **alias, list_t **env);
int unsetenv_builtin(char **commands, list_t **alias, list_t **env);
int help_builtin(char **commands, char **env);
int history_builtin(char **commands, char **env);
int cd_builtin(char **commands, char **env);
int alias_builtin(char **commands, list_t **alias, list_t **env);

/* Misc */
void print_memory_hex(char *buffer, unsigned long int buffer_size);
void print_parse(char **command);
void print_parsed_line(char **command);

/* List manipulation */
list_t *add_node(list_t **head, int idx, char *s);
void print_list(list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);

char *get_var(char *var, list_t *env);
int add_to_list(list_t **env, char *varN, char *varV);
int del_from_list(list_t **env, char *varN);

/* Environment */
list_t *copy_env(char **env);

#endif
