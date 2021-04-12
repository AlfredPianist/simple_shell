#include "test.h"

char *_strcpy(char *dest, char *src)
{
	int c;

	for (c = 0; src[c] != '\0' ; c++)
		dest[c] = *(src + c);
	dest[c] = *(src + c);

	return (dest);
}


int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (str[i++])
		;

	return (i);
}

char *_strcat(char *dest, char *src)
{
	int i = 0, size = 0, j = 0;

	while (dest[i++])
		size++;

	for (j = 0; src[j] != '\0'; j++, size++)
		dest[size] = src[j];

	dest[size] = 0;

	return (dest);
}

char *nstrcat(const int tot_strs, ...)
{
	int counter = 0;
	char *final_str = NULL, *curr_str;
	va_list strings;

	va_start(strings, tot_strs);
	do {
		curr_str = va_arg(strings, char *);
		final_str = _realloc(final_str, _strlen(final_str),
				     _strlen(final_str) + _strlen(curr_str));
		_strcat(final_str, curr_str);
		counter++;
	} while (counter < tot_strs);
	va_end(strings);

	return (final_str);
}
