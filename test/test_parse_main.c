#include "test.h"

int main(void)
{
	char **parsed = NULL;
	char *token = NULL;
	char ignore[] = "'";
	char *line1 = NULL;
	char line2[] = "testing spaces and:colons";
	char line3[] = "testing\ttabs";
	char line4[] = "testing\nnew\nline";
	char line5[] = "testing=equal";
	char line6[] = "Everything\t\t        testing\ntesting::something\rI:hope\rit     works";
	char line7[] = "ignoring 'simple quotation marks'";

	line1 = _realloc(line1, 0, _strlen("testing spaces"));
	_strcat(line1, "testing spaces");
	printf("Line 1:\n%s\n", line1);
	parsed = parse_line(parsed, line1, " ", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);
	printf("Freeing line 1\n");
	free(line1);

	parsed = NULL;
	printf("----------\nLine 2:\n%s\n", line2);
	parsed = parse_line(parsed, line2, " :", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);

	parsed = NULL;
	printf("----------\nLine 3:\n%s\n", line3);
	parsed = parse_line(parsed, line3, "\t", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);

	parsed = NULL;
	printf("----------\nLine 4:\n%s\n", line4);
	parsed = parse_line(parsed, line4, "\n", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);

	parsed = NULL;
	printf("----------\nLine 5:\n%s\n", line5);
	parsed = parse_line(parsed, line5, "=", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);

	parsed = NULL;
	printf("----------\nLine 6:\n%s\n", line6);
	parsed = parse_line(parsed, line6, " :\t\n\r", ignore);
	print_parsed_line(parsed);
	free_strs_array(parsed);

	return (EXIT_SUCCESS);
}