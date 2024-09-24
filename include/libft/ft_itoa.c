/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:07 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/24 11:21:39 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	nbr_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len ++;
	}
	return (len);
}

static char	*nstr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	else
		return (str);
}

static long long	absolute(long long n)
{
	long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				neg;
	int				len;
	char			*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	if (n < 0)
		neg = 1;
	len = nbr_len(n);
	str = nstr(len);
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	nbr = absolute(n);
	while (len--)
	{
		*(str + len) = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (neg)
		*(str) = 45;
	return (str);
}
