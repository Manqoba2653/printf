#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints character
 * @types: List the arguments
 * @buffer: Buffer array will handle print
 * @flags: To calculates active flags
 * @width: The width
 * @precision: The specification of precision
 * @size: The size specifier
 * Return: The number of characters to be printed
 */

int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Prints the string
 * @types: List arguments
 * @buffer: Buffer array handle print
 * @flags: To calculate the active flags
 * @width: To get the width.
 * @precision: The specification of precision
 * @size: The size specifier
 * Return: The number of characters to be printed
 */

int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, a;
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
	
	while (str[length] != '\0')
		length++;
	
	if (precision >= 0 && precision < length)
		length = precision;
	
	if (width > length)
	{
		if (flags & F_MINUS)
                {
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	
	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - To print a percent sign
 * @types: The list of the arguments
 * @buffer: The buffer array to handle print
 * @flags:  To calculate the active flags
 * @width: To get the width.
 * @precision: The precision specification
 * @size: The size specifier
 * Return: The number of characters to be printed
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

/************************* PRINT INT *************************/

/**
 * print_int - Print int
 * @types: The list of arguments
 * @buffer: The buffer array to handle print
 * @flags: To calculate the active flags
 * @width: To get the width.
 * @precision: The precision specification
 * @size: The size specifier
 * Return: The number of characters to be printed
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int num;
	
	b = convert_size_number(b, size);
	
	if (b == 0)
		buffer[i--] = '0';
	
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)b;
	
	if (b < 0)
	{
		num = (unsigned long int)((-1) * b);
		is_negative = 1;
	}
	
	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}
	
	a++;
	
	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - To print an unsigned number
 * @types: A list of arguments
 * @buffer: The buffer array to handle print
 * @flags:  To calculate active flags
 * @width: To get width.
 * @precision: The precision specification
 * @size: The size specifier
 * Return: The numbers of characters to be printed.
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int b, m, a, sum;
	unsigned int a[32];
	int count;
	
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	
	b = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = b / m;
	for (a = 1; a < 32; a++)
	{
		m /= 2;
		a[a] = (b / m) % 2;
	}
	for (a = 0, sum = 0, count = 0; a < 32; a++)
	{
		sum += a[a];
		if (sum || a == 31)
		{
			char z = '0' + a[a];
			
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
