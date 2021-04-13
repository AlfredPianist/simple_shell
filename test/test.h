#ifndef TEST
#define TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

list_t *add_node(list_t **head, int idx, char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void print_list(list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);

int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *nstrcat(int tot_strs, ...);
char *_strcpy(char *dest, char *src);
char *_strpbrk(char *s, char *accept);

char *_strncat(char *dest, char *src, int n);
int is_delim(char curr_char, char *delims);
int count_tokens(char *line, char *delims, char *ignore);
int is_substring(char *line, char *ignore);
char *substring(char *line, char *ignore, int len);
char *new_token(char **line, char *delims);
char **parse_line(char *line, char *delims, char *ignore);
void print_parsed_line(char **command);
void free_strs_array(char **strs_array);

char *alias_value(char *line);

#endif
