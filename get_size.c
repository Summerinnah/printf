#include "main.h"

/**
 * get_size - function calculates the size to cast the argument
 * @format: string
 * @i: input
 * Return: 0
 */

int get_size(const char *format, int *i)
{
	int curries_i = *i + 1;
	int size = 0;

	if (format[curries_i] == 'l')
		size = S_LONG;
	else if (format[curries_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curries_i - 1;
	else
		*i = curries_i;

	return (size);
}
