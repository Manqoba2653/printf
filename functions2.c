#include "main.h"

/****************** PRINT POINTER ******************/

/**
* print_pointer - To print the value of a pointer variable
* @types: A list of arguments
* @buffer: A buffer array to handle print
* @flags: To calculates active flags
* @width: To get the width
* @precision: The Precision specification
* @size: The size specifier
* Return: The number of characters to be printed.
*/

int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);
	
	UNUSED(width);
	UNUSED(size);
	
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	
	buffer[BUFF_SIZE - 1] = '\0';
	
	UNUSED(precision);
	
	num_addrs = (unsigned long)addrs;
	
	while (num_addrs > 0)
	{
		buffer[ind--] = map_to [num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	
	if (flags & F_PLUS)
		extra_c = '+', length++;
	
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	
	ind++;
	
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
				width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
* print_non_printable - To print ascii codes in hexa of non printable chars
* @types: A list of arguments
* @buffer: The buffer array to handle print
* @flags: To calculate active flags
* @width: To get width
* @precision: The precision specification
* @size: The size specifier
* Return: The number of characters to be printed
*/

int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = 0, offset = 0;
	char *str = va_arg(types, char *);
	
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	
	if (str == NULL)
		return (write(1, "(null)", 6));
	
	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + offset] = str[a];
		
		else
			offset += append_hexa_code(str[a], buffer, a + offset);
		
		a++;
	}
	
	buffer[a + offset] = '\0';
	
	return (write(1, buffer, a + offset));
}

/************************* PRINT REVERSE *************************/
/**
* print_reverse - To print a reverse string.
* @types: To list arguments
* @buffer: A buffer array to handle print
* @flags: To calculate active flags
* @width: To get width
* @precision: The precision specification
* @size: A size specifier
* Return: The number of characters to be printed
*/

int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int a, count = 0;
	
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	
	str = va_arg(types, char *);
	
	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}
	for (a = 0; str[a]; a++);
	
	for (i = a - 1; a >= 0; a--)
	{
		char z = str[a];
		
		write(1, &z, 1);
		count++;
	}
	
	return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/

/**
* print_rot13string - To print a string in rot13.
* @types: To list arguments
* @buffer: A buffer array to handle print
* @flags: To calculate active flags
* @width: To get width
* @precision: A precision specification
* @size: A size specifier
* Return: The number of characters to be printed
*/

int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int a, b;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	
	str = va_arg(types, char *);
	
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	
	if (str == NULL)
		str = "(AHYY)";
	
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				x = out[b];
				write(1, &x, 1);
				count++;
				
				break;
			}
		}
		
		if (!in[b])
		{
			x = str[a];
			write(1, &x, 1);
			count++;
		}
	}
	
	return (count);
}
