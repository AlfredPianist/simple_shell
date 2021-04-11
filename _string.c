#include "header.h"
/**
 * _strcpy - copies the string pointed to by src
 * to the buffer pointed to by dest.
 * @dest: pointer to save the string
 * @src: string to save in desc
 * Return: the new value saved in dest
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
 * _strcat - concatenates two strings
 * @dest: first string to concatenate and the final result
 * @src: second string to concatenate
 * Return: the full concatenated string
 */
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

int _strcmp(char *s1, char *s2)
{

        while (*s1 && *s2 && (*s1 == *s2))
        {
                s1++;
                s2++;
        }

        return (*s1 - *s2);
}
/**
 * _strncmp - compare two string n characters
 * @s1: string to compare
 * @s2: string to compare
 * @@n: characters to compare
 * Return: the diference of chars's strings
 */
int _strncmp(char *s1, char *s2, int n)
{

        while (*s1 && *s2 && (*s1 == *s2) && n)
        {
                s1++;
                s2++;
                n--;
        }
        if (n == 0)
                return (0);
                
        return (*s1 - *s2);
}

/**
 * _atoi - convert string to number
 * @s: string to convert
 * Return: string number to int format
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

/**
 * _strlen - returns the length of a string
 * @s: string to check the size
 * Return: size of string
 */

int _strlen(char *str)
{
	int i = 0;

	while(str[i])
		i++;

	return (i);
}
