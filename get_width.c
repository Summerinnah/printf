#include "main.h"

/**
 * get_width - function calculates the width for printing
 * @format: string
 * @i: input
 * @list: input
 * Return: width
 */

int get_width(const char *format, int *i, va_list list)
{
	int calculates;
	int width = 0;

	for (calculates = *i + 1; format[calculates] != '\0'; calculates++)
	{
		if (is_digit(format[calculates]))
		{
			width *= 10;
			width += format[calculates] - '0';
		}
		else if (format[calculates] == '*')
		{
			calculates++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = calculates - 1;

	return (width);
}
