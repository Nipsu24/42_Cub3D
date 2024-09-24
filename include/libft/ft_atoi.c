/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:49:08 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/24 09:59:33 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ovr_flw(int neg)
{
	if (neg == 1)
		return ((int) FT_LONG_MAX);
	return ((int)-FT_LONG_MAX - 1L);
}

int	ft_atoi(const char *str)
{
	long long	rtn;
	int			neg;
	int			i;
	int			pre;

	rtn = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		pre = rtn;
		rtn = (rtn * 10) + (str[i] - 48);
		if (rtn < 0 || pre > rtn)
			return (ovr_flw(neg));
		i++;
	}
	return (rtn * neg);
}
