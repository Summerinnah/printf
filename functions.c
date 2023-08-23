#include "main.h"

/**
 * print_char - function that Prints a char
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of characters printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char b = va_arg(types, int);

	return (handle_write_char(b, buffer, flags, width, precision, size));
}

/**
 * print_string - function that Prints a string
 * @types: input
 * @buffer: input
 * @flags:  input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of characters printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}

/**
 * print_percent - function that Prints a percent sign
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - function that Prints an integer
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: 0
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int sum;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	sum = (unsigned long int)n;

	if (n < 0)
	{
		sum = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (sum > 0)
	{
		buffer[i--] = (sum % 10) + '0';
		sum /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}


/**
 * print_binary - function that Prints unsigned number
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: 0
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int c, d, i, num;
	unsigned int a[32];
	int lists;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	c = va_arg(types, unsigned int);
	d = 2147483648; /* (2 ^ 31) */
	a[0] = c / d;
	for (i = 1; i < 32; i++)
	{
		d /= 2;
		a[i] = (c / d) % 2;
	}
	for (i = 0, num = 0, lists = 0; i < 32; i++)
	{
		num += a[i];
		if (num || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			lists++;
		}
	}
	return (lists);
}
