#include "main.h"

/**
 * print_unsigned - function that prints an unsigned number
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of characters printed.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int sum = va_arg(types, unsigned long int);

	sum = convert_size_unsgnd(sum, size);

	if (sum == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (sum > 0)
	{
		buffer[i--] = (sum % 10) + '0';
		sum /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - function that prints an unsigned number in octal
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: 0
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int sum = va_arg(types, unsigned long int);
	unsigned long int isit_sum = sum;

	UNUSED(width);

	sum = convert_size_unsgnd(sum, size);

	if (sum == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (sum > 0)
	{
		buffer[i--] = (sum % 8) + '0';
		sum /= 8;
	}

	if (flags & F_HASH && isit_sum != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - function prints an unsigned number in hexadecimal
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of characters printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - function prints unsigned number in upper hexadecimal
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of characters printed
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: input
 * @map_to: input
 * @buffer: input
 * @flags: input
 * @flag_ch: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: 0
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
