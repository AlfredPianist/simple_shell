#include "test.h"

int main(void)
{
	char str1[] = "Hello ";
	char str2[] = "World ";
	char str3[] = "Testing ";
	char str4[] = "Is this working?";
	char *dest = NULL;
	char *cpy = NULL;

	dest = nstrcat(4, str1, str2, str3, str4, "\n");
	/* printf("%s", dest); */
	free(dest);

	cpy = malloc(sizeof(*cpy) * _strlen(str1));
	_strcpy(cpy, str1);
	printf("%s", cpy);
	free(cpy);

	exit(EXIT_SUCCESS);
}
