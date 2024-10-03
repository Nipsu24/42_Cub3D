/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:18:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/03 11:05:21 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int	get_length(char **arr)
{
	static int	x = 0;
	static int	y = 0;
	static int	i = 0;

	while (arr[y])
	{
		if ((arr[y][x] == ' ') || (arr[y][x] == '1'))
		{
			while (arr[y])
			{
				y++;
				i++;
			}
			break ;
		}
		y++;
	}
	return (i);
}

int	map_extract(t_data *data)
{
	static int	x = 0;
	static int	y = 0;
	static int	z = 0;
	static int	len = 0;

	len = get_length(data->file_arr);
	data->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!data->map)
		return (1);
	while (data->file_arr[y])
	{
		if ((data->file_arr[y][x] == ' ') || (data->file_arr[y][x] == '1'))
		{
			data->map[z] = ft_strdup(data->file_arr[y]);
			if (!data->map[z])
			{
				free_arr_rev(&data->map, z);
				return (1);
			}
			z++;
		}
		y++;
	}
	data->map[z] = NULL;
	return (0);
}
