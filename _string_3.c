#include "header.h"

/**
 * _itoa - convert a integer into a string
 * @buffsize: The size of the buffer.
 * @sign: The minus sign.
 * @num: The number to be converted to alpha.
 * @nums: A buffer of minimun 12 bytes to store  the number as a string.
 *
 * Return: A pointer to the first byte of the string.
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
