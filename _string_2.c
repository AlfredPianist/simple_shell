#include "header.h"

/**
 * *_strpbrk - searches a string for any of a set of bytes.
 * @s: the source string.
 * @accept: the substring of accepted characters.
 *
 * Return: a pointer to the byte in s that matches one of the bytes in accept,
 *         or NULL if not found.
 */
char *_strpbrk(char *s, char *accept)
{
	unsigned int index_s, index_a;
	char *res = NULL;

	for (index_s = 0; s[index_s] != '\0' && res == NULL; index_s++)
	{
		for (index_a = 0; accept[index_a] != '\0'; index_a++)
		{
			if (s[index_s] == accept[index_a])
			{
				res = s + index_s;
				break;
			}
		}
	}

	return (res);
}

/**
 * _strdup - Duplicates a string allocating memory for it.
 * @str: The source string.
 *
 * Return: A duplication of the string.
 */
char *_strdup(char *str)
{
	char *dup = NULL;

	dup = _realloc(dup, 0, sizeof(*dup) * _strlen(str) + 1);
	if (dup == NULL)
		return (NULL);

	dup = _strcpy(dup, str);

	return (dup);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: First string to concatenate and the final result.
 * @src: Second string to concatenate.
 *
 * Return: The full concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, size = 0, j = 0;

	while (dest[i++])
		size++;

	for (j = 0; src[j] != '\0'; j++, size++)
		dest[size] = src[j];

	dest[size] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates two strings, given n amount of characters.
 * @dest: First string to concatenate and the final result.
 * @src: Second string to concatenate.
 * @n: The amount of characters to concatenate.
 *
 * Return: The full concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, size = 0, j = 0;

	while (dest[i++])
		size++;

	for (j = 0; src[j] && j < n; j++, size++)
		dest[size] = src[j];

	dest[size] = '\0';

	return (dest);
}

/**
 * nstrcat - Concatenates n strings to a final one.
 * @tot_strs: The total strings to be concatenated.
 *
 * Description: This function creates a full concatenated string from
 *              a varied set of individual strings, this final string is also
 *              allocated in memory, so the user should free it in his own
 *              program.
 * Return: The full concatenated string.
 */
char *nstrcat(const int tot_strs, ...)
{
	int counter = 0;
	char *final_str = NULL, *curr_str;
	va_list strings;

	va_start(strings, tot_strs);
	do {
		curr_str = va_arg(strings, char *);
		final_str = _realloc(final_str, _strlen(final_str) + 1,
				     _strlen(final_str) + _strlen(curr_str) + 1);
		if (final_str == NULL)
			return (NULL);

		_strcat(final_str, curr_str);
		counter++;
	} while (counter < tot_strs);
	va_end(strings);

	return (final_str);
}
