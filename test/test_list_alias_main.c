#include "test.h"

int main(void)
{
	alias_t *alias = NULL;
	char line[] = "l='ls -CF' la='ls -A' la ll='ls -alF'";

	printf("Line = %s\n", line);
	parse_line_alias(line, &alias);
	/* print_list_alias(alias); */
	/* print_alias_name(alias, "l"); */
	/* print_alias_name(alias, "ly"); */
	/* free_list_alias(&alias); */

	return (EXIT_SUCCESS);
}
