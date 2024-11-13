/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/13 11:52:25 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Checks if there are any digits in every string of the array and
  returns 0 if this is not the case.*/

static int	texture_extract_helper_2(t_data *data, int y, int x, t_img *img)
{
	if (ft_strncmp("WE ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_west(&data->file_arr[y][x], img))
			return (1);
	}
	else if (ft_strncmp("C ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_c(data->file_arr[y], img, 0, 0))
			return (free_dir(img));
	}
	else if (ft_strncmp("F ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_f(data->file_arr[y], img, 0, 0))
			return (free_dir(img));
	}
	return (0);
}

static int	texture_extract_helper_1(t_data *data, int y, int x, t_img *img)
{
	if (ft_strncmp("NO ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_north(&data->file_arr[y][x], img))
			return (1);
	}
	else if (ft_strncmp("EA ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_east(&data->file_arr[y][x], img))
			return (1);
	}
	else if (ft_strncmp("SO ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_south(&data->file_arr[y][x], img))
			return (1);
	}
	else
	{
		if (texture_extract_helper_2(data, y, x, img))
			return (1);
	}
	return (0);
}

int	texture_extract(t_data *data, t_img *img, int x, int y)
{
	static int	count = 0;

	while (data->file_arr[++y])
	{
		while (data->file_arr[y][x])
		{
			if ((ft_strncmp("NO ", &data->file_arr[y][x], 3) == 0) ||
			(ft_strncmp("EA ", &data->file_arr[y][x], 3) == 0) ||
			(ft_strncmp("SO ", &data->file_arr[y][x], 3) == 0) ||
			(ft_strncmp("WE ", &data->file_arr[y][x], 3) == 0) ||
			(ft_strncmp("F ", &data->file_arr[y][x], 2) == 0) ||
			(ft_strncmp("C ", &data->file_arr[y][x], 2) == 0))
			{
				count++;
				if (texture_extract_helper_1(data, y, x, img))
					return (1);
				if (count == 6)
					data->map_start = y + 1;
			}
			break ;
		}
	}
	if ((range_check(img->floor)) || (range_check(img->ceiling)))
		return (err_msg(9));
	return (0);
}
