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

#endif