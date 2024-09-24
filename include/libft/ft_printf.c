/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:45:15 by lstorey           #+#    #+#             */
/*   Updated: 2024/01/31 14:52:43 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		temp;
	int		check;

	check = 0;
	count = 0;
	va_start(ap, format);
	while (*format)
	{
		temp = 0;
		if (*format == '%')
		{
			++format;
			temp += print_format(*format, ap, &check);
		}
		else
			temp += print_char(*format, &check);
		format++;
		count += temp;
	}
	va_end(ap);
	if (check == -1)
		return (-1);
	return (count);
}

int	print_format(char specifier, va_list ap, int *check)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = print_char(va_arg(ap, int), check);
	else if (specifier == 's')
		count = print_str(va_arg(ap, char *), check);
	else if (specifier == 'p')
		count = print_pnt((unsigned long)va_arg(ap, void *), 16, check);
	else if (specifier == 'd' || specifier == 'i')
		count = print_digit(va_arg(ap, int), 10, check);
	else if (specifier == 'u')
		count = print_digit(va_arg(ap, unsigned int), 10, check);
	else if (specifier == 'x')
		count = print_hex_lower((long)va_arg(ap, unsigned int), 16, check);
	else if (specifier == 'X')
		count = print_hex_upper((long)va_arg(ap, unsigned int), 16, check);
	else
		count = print_char(specifier, check);
	return (count);
}
