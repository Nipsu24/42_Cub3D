/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/02 14:47:04 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_c(char *address, t_img *img, int i, int c)
{
	char **tmp_arr;

	address++;
	while (address[i])
	{
		if (address[i] ==',')
			c++;
		i++;
	}
	if (c > 2 || number_count(address))
	{
		err_msg(8);
		return (1);
	}
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr)
		return(1);
	img->ceiling[0] = ft_atol(tmp_arr[0]);
	img->ceiling[1] = ft_atol(tmp_arr[1]);
	img->ceiling[2] = ft_atol(tmp_arr[2]);
	free_arr(&tmp_arr);
	return (0);
}
static int	get_f(char *address, t_img *img, int i, int c)
{
	char **tmp_arr;

	address++;
	while (address[i])
	{
		if (address[i] ==',')
			c++;
		if (address[i] != ',' && address[i] != ' ' && !ft_isdigit(address[i]))
		{
			err_msg(8);
			return (1);
		}	
		i++;
	}
	if (c > 2 || number_count(address))
	{
		err_msg(8);
		return (1);
	}
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr)
		return(1);
	img->floor[0] = ft_atol(tmp_arr[0]);
	img->floor[1] = ft_atol(tmp_arr[1]);
	img->floor[2] = ft_atol(tmp_arr[2]);
	free_arr(&tmp_arr);
	return (0);
}

static int	texture_extract_helper_2(t_data *data, int y, int x, t_img *img)
{
	if (ft_strncmp("WE ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_west(&data->file_arr[y][x], img))
			return (1);
	}
	else if (ft_strncmp("C ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_c(&data->file_arr[y][x], img, 0, 0))
			return (free_dir(img));
	}
	else if (ft_strncmp("F ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_f(&data->file_arr[y][x], img, 0, 0))
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
	else if(ft_strncmp("EA ", &data->file_arr[y][x], 3) == 0)
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
	while(data->file_arr[++y])
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
				if (texture_extract_helper_1(data, y, x, img))
					return (1);
			}
			break;		
		}
	}
	if ((range_check(img->floor)) || (range_check(img->ceiling)))
	{
		err_msg(9);
		return (1);
	}
	return (0);
}
