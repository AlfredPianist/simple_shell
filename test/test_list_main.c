#include "test_list.h"

int main(void)
{
	list_t *node;

	node = NULL;

	printf("Add nodes:\n");
	add_node(&node, 0, "First");
	add_node(&node, 1, "Second");
	add_node(&node, 2, "Third");
	add_node(&node, 3, "Fourth");
	add_node(&node, 4, "Fifth");
	add_node(&node, 5, "Sixth");
	print_list(node);

	printf("---------\n");
	printf("Add last node:\n");
	add_node(&node, -1, "Last 1");
	add_node(&node, -1, "Last 2");
	print_list(node);

	printf("---------\n");
	printf("Add node at index:\n");
	add_node(&node, 2, "Index 2");
	add_node(&node, 5, "Index 5");
	print_list(node);

	printf("---------\n");
	printf("Add error:\n");
	add_node(&node, -10, "Error 1");
	add_node(&node, 20, "Error 2");
	print_list(node);

	printf("---------\n");
	printf("Deletes at index:\n");
	delete_node_at_index(&node, 0);
	delete_node_at_index(&node, 5);
	delete_node_at_index(&node, 2);
	delete_node_at_index(&node, 6);
	print_list(node);

	printf("---------\n");
	printf("Deletes at index error:\n");
	delete_node_at_index(&node, 80);
	delete_node_at_index(&node, -10);
	print_list(node);

	printf("---------\n");
	printf("Frees list:\n");
	free_list(&node);
	print_list(node);

	exit(EXIT_SUCCESS);
}
