#include "main.h"

/**
 * is_printable - Evaluates if a character is printable
 * @c: The character to be evaluated.
 *
 * Return: To return 1 if c is printable, 0 otherwise
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);
	
	return (0);
}

/**
 * append_hexa_code - To append ascci in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always return 3
 */

int append_hexa_code(char ascii_code, char buffer[], int a)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;
	
	buffer[a++] = '\\';
	buffer[a++] = 'x';
	
	buffer[a++] = map_to[ascii_code / 16];
	buffer[a] = map_to[ascii_code % 16];
	
	return (3);
}

/**
 * is_digit - Verifies if a character is a digit
 * @c: The character to be evaluated
 *
 * Return: Return 1 if c is a digit, 0 otherwise
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	
	return (0);
}

/**
 * convert_size_number - Will casts a number to the specified size
 * @num: The number to be casted.
 * @size: The number indicating the type to be casted.
 *
 * Return: To return casted value of num
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);
	
	return ((int)num);
}

/**
 * convert_size_unsgnd - To cast a number to the specified size
 * @num: The number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: To return casted value of num
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);
	
	return ((unsigned int)num);
}
