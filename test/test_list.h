#ifndef TEST_LIST
#define TEST_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

list_t *add_node(list_t **head, int idx, char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void print_list(list_t *head);
void free_list(list_t **head);

#endif
