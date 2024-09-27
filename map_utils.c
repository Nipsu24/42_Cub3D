/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:18:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/27 16:34:17 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int get_length(char **arr)
{
	static int x = 0;
	static int y = 0;
	static int i = 0;

	while(arr[y])
	{
		if ((arr[y][x] == ' ') || (arr[y][x] == '1'))
		{
			while(arr[y])
			{
				y++;
				i++;
			}
			break;
		} 
		y++;
	}
	return (i);
}

void	map_extract(t_data *data)
{
	static int	x = 0;
	static int	y = 0;
	static int	z = 0;
	static int	len = 0;
	
	len = get_length(data->file_arr);
	data->map = (char **)malloc(sizeof(char *) * len + 1);
	if (!data->map)
	{
		err_msg(5);
	}
	while(data->file_arr[y])
	{
		if ((data->file_arr[y][x] == ' ') || (data->file_arr[y][x] == '1'))
		{
			data->map[z] = ft_strdup(data->file_arr[y]);
			z++;
		}
		y++;
	}
	data->map[z] = NULL;
}
