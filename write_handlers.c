#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: character types.
 * @buffer: A buffer array to handle print
 * @flags: To calculate active flags.
 * @width: To get width.
 * @precision: A precision specifier
 * @size: A size specifier
 *
 * Return: Return a number of characters to be printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int a = 0;
	char padd = ' ';
	
	UNUSED(precision);
	UNUSED(size);
	
	if (flags & F_ZERO)
		padd = '0';
	
	buffer[a++] = c;
	buffer[a] = '\0';
	
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = padd;
		
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	
	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: A list of arguments
 * @ind: character types.
 * @buffer: A buffer array to handle print
 * @flags:  To calculate active flags
 * @width: To get width.
 * @precision: A precision specifier
 * @size: A size specifier
 *
 * Return: Return a number of character to be printed.
 */

int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;
	
	UNUSED(size);
	
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	
	return (write_num(ind, buffer, flags, width, precision,
				length, padd, extra_ch));
}

/**
 * write_num - To write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: A precision specifier
 * @length: Number length
 * @padd: Pading character
 * @extra_c: Extra character
 *
 * Return: Return number of printed characters.
 */

int write_num(int ind, char buffer[],
		int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int a, padd_start = 1;
	
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], a - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - To writes an unsigned number
 * @is_negative: A number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: A precision specifier
 * @size: The size specifier
 *
 * Return: Return number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
		char buffer[],
		int flags, int width, int precision, int size)

{
	/* The number is stored at the bufer's right and starts at position a */
	int length = BUFF_SIZE - ind - 1, a = 0;
	char padd = ' ';
	
	UNUSED(is_negative);
	UNUSED(size);
	
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	
	if (precision > 0 && precision < length)
		padd = ' ';
	
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	
	if (width > length)
	{
		for (i = 0; a < width - length; a++)
			buffer[a] = padd;
		
		buffer[a] = '\0';
		
		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], a));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], length));
		}
	}
	
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - To write a memory address
 * @buffer: The arrays of characters
 * @ind: Index at which the number starts in the buffer
 * @length: The length of number
 * @width: The width specifier
 * @flags: A flags specifier
 * @padd: A character representing the padding
 * @extra_c: Character representing extra character
 * @padd_start: Index at which padding should start
 *
 * Return: Return number of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int a;
	
	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
