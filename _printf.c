#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - prints printf function
 * @format: character string
 * Return: number of characters printed
 */

int _printf(const char *format, ...)
{
	int i, print = 0, printed_chars = 0;
	int flags, field_width, precision, length, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			fieldwidth = get_fieldwidth(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_length(format, &i);
			++i;
			print = handle_print(format, &i, list, buffer,
				flags, fieldwidth, precision, length);
			if (print == -1)
				return (-1);
			printed_chars += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: input
 * @buff_ind: input
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
