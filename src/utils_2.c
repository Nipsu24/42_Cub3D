/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:31 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/02 15:30:31 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int number_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if(ft_isdigit(str[i]))
		{
			c++;
			while (ft_isdigit(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	if (c > 3)
		return (1);
	return (0);
}
