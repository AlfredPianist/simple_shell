#ifndef TEST
#define TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* List (env & hist) */
list_t *add_node(list_t **head, int idx, char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void print_list(list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);

/* List manipulation (alias) */
alias_t *add_node_alias(alias_t **head, int idx, char *var, char *val);
void parse_line_alias(char *line, alias_t **alias);
void print_list_alias(alias_t *head);
int print_alias_name(alias_t *head, char *name);
void free_list_alias(alias_t **head);

/* String manipulation */
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *nstrcat(int tot_strs, ...);
char *_strcpy(char *dest, char *src);
char *_strpbrk(char *s, char *accept);
char *_strdup(char *str);

/* Parsing */
char *_strncat(char *dest, char *src, int n);
int is_delim(char curr_char, char *delims);
int count_tokens(char *line, char *delims, char *ignore);
int is_substring(char *line, char *ignore);
char *substring(char *line, char *ignore, int len);
char *new_token(char **line, char *delims);
char **parse_line(char *line, char *delims, char *ignore);
void print_parsed_line(char **command);
void free_strs_array(char **strs_array);

#endif
