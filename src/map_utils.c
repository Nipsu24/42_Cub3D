/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:18:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/11 12:09:37 by lstorey          ###   ########.fr       */
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

static int	zero_at_start(char **arr)
{
	static int	y = 0;

	while (arr[y])
	{
		if (arr[y][0] == '0')
		{
			err_msg(8);
			return (1);
		}
		y++;
	}
	return (0);
}

int	map_extract(t_data *data)
{
	static int	y;
	static int	z = 0;
	static int	len = 0;

	len = get_length(data->file_arr);
	if (zero_at_start(data->file_arr))
		return (1);
	data->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!data->map)
		return (1);
	y = data->map_start -1;
	while (data->file_arr[++y])
	{
		data->map[z] = ft_strdup(data->file_arr[y]);
		if (!data->map[z])
		{
			free_arr_rev(&data->map, z);
			return (1);
		}
		z++;
	}
	data->map[z] = NULL;
	return (0);
}
