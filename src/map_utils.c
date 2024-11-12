/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:18:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/12 16:06:19 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Helper function of map_extract. As it is assumed that
  the map values (textures, ceiling, floor) are on the
  first 5 lines of the 2d array (0 to 5), y starts at 6.*/
static int	get_length(char **arr)
{
	static int	y = 6;
	static int	i = 0;

	while (arr[y])
	{
		y++;
		i++;
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

/*Creates 2d array of map taken from cub file. It is assumed at this point
  that the previous map values (textures, ceiling, floor) are correct and
  on the first 5 lines of the 2d array (0 to 5), therefore y starts at 6.*/
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
	y = 5;
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
