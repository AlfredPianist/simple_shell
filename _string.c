#include "header.h"

/**
 * _strlen - Returns the length of a string.
 * @str: String to check its size.
 *
 * Return: Size of the string.
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (str[i])
		i++;

	return (i);
}

/**
 * _strcpy - Copies the string pointed to by src
 *           to the buffer pointed to by dest.
 * @dest: Pointer to save the string.
 * @src: String to save in dest.
 *
 * Return: The new string saved in dest.
 */
char *_strcpy(char *dest, char *src)
{
	int c;

	for (c = 0; src[c] != '\0' ; c++)
		dest[c] = *(src + c);
	dest[c] = *(src + c);

	return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The difference of characters between strings. 0 if equal.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
		s1++, s2++;

	return (*s1 - *s2);
}

/**
 * _strncmp - Compare n amount of characters from two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The amount of characters to compare.
 *
 * Return: The diference of characters between strings. 0 if equal.
 */
int _strncmp(char *s1, char *s2, int n)
{
	while (*s1 && *s2 && (*s1 == *s2) && n)
		s1++, s2++, n--;

	if (n == 0)
		return (0);

	return (*s1 - *s2);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: String to convert.
 *
 * Return: String number to int format.
 */
int _atoi(char *s)
{
	int c, sign = 1;
	unsigned int result = 0;

	for (c = 0; s[c] != '\0' ; c++)
		if (s[c] == '-')
			sign *= -1;
		else if (s[c] >= '0' && s[c] <= '9')
			result = (result * 10) + (s[c] - '0');
		else if (result)
			break;

	return (result * sign);
}
