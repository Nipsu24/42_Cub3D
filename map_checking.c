/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:23:52 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 12:20:36 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	err_msg(int err_flag)
{
	if (err_flag == 0)
		printf("Error. Empty line(s) in map.\n");
	return (1);
}

int	only_spaces_str(data *data)
{
	int	j;
	int	flag_no_space;
	int	i;

	j = -1;
	i = -1;
	flag_no_space = 0;
	while (j++, data->map[j])
	{
		flag_no_space = 0;
		i = 0;
		while (i++, data->map[j][i])
		{
			if (data->map[j][i] != ' ')
				flag_no_space = 1;
		}
		if (flag_no_space == 0)
			return (err_msg(0));
	}
	return (0);
}

int	map_checker (data *data)
{
	if (only_spaces_str(data))
		return (free_input(data));
	if (not_rectangular(data));
	return (0);
}
