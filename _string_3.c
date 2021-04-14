#include "header.h"

char *_substring(char *s,int start, int trv)
{
	char *ss = malloc(sizeof(char) * (trv - start + 1));

	if (!ss)
		return (0);

	while (start < trv)
		ss[start] = s[start], start++;

	ss[start] = 0;

	return (ss);
}

/**
 * itoa - convert a integer into a string
 * @num: number
 * @nums: buffer of minimun 12 bytes to storage the number as a string
 * @sign: sing char
 * Return: pointer to first byte of number as a string
 */
char *_itoa(int buffsize, char sign, unsigned long int num, char *nums)
{
	int i = buffsize - 2, negative = 0, digit;

	nums[buffsize - 1] = 0;
	if (sign == '-')
	{
		negative = 1;
	}
	do {
		digit = num % 10;
		digit = (digit < 0) ? -digit : digit;
		nums[i] = digit + '0';
		num = num / 10;
		i--;
	} while (num);
	if (negative)
	{
		nums[i] = '-';
		return (nums + i);
	}
	return (nums + i + 1);
}
