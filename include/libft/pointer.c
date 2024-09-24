/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:24:37 by lstorey           #+#    #+#             */
/*   Updated: 2024/01/31 14:53:05 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_pnt(unsigned long n, unsigned long base, int *check)
{
	int		count;

	count = 0;
	if (!n)
		return (print_str("0x0", check));
	else
	{
		count += print_str("0x", check);
		if (n < base)
			return (count += print_hex_lower((n / base), base, check));
		{
			count += print_hex_lower((n / base), base, check);
			return (count += print_hex_lower(n % base, base, check));
		}
	}
}
