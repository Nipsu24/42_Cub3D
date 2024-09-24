/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:58:40 by lstorey           #+#    #+#             */
/*   Updated: 2024/01/31 14:53:11 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int c, int *check)
{
	if (*check == -1)
		return (-1);
	if (write(1, &c, 1) == -1)
	{
		*check = -1;
		return (-1);
	}
	return (1);
}

int	print_str(char *s, int *check)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (print_str("(null)", check));
	while (s[i])
	{
		print_char((int)s[i], check);
		i++;
	}
	return (i);
}

int	print_digit(long n, int base, int *check)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		print_char('-', check);
		return (print_digit(-n, base, check) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n], check));
	else
	{
		count = print_digit((n / base), base, check);
		return (count + print_digit(n % base, base, check));
	}
}
