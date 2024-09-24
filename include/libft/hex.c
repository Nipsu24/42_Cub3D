/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:08:50 by lstorey           #+#    #+#             */
/*   Updated: 2024/01/31 14:52:52 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex_lower(long n, int base, int *check)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		print_char('-', check);
		return (print_hex_lower(-n, base, check) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n], check));
	else
	{
		count = print_hex_lower((n / base), base, check);
		return (count + print_hex_lower(n % base, base, check));
	}
}

int	print_hex_upper(long n, int base, int *check)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		print_char('-', check);
		return (print_hex_upper(-n, base, check) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n], check));
	else
	{
		count = print_hex_upper((n / base), base, check);
		return (count + print_hex_upper(n % base, base, check));
	}
}
