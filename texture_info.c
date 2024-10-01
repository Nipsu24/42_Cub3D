/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/01 12:01:32 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	texture_extract_helper_2(t_data *data, int y, int x, t_img *img)
{
	if (ft_strncmp("WE ", &data->file_arr[y][x], 3) == 0)
	{
		if (get_west(&data->file_arr[y][x], img))
			return (1);
	}
	else if (ft_strncmp("C ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_c(&data->file_arr[y][x], img))
			return (free_dir(img));
	}
	else if (ft_strncmp("F ", &data->file_arr[y][x], 2) == 0)
	{
		if (get_f(&data->file_arr[y][x], img))
			return (free_dir(img));
	}
	return (0);
}

int	texture_extract_helper_1(t_data *data, int y, int x, t_img *img)
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
	return (0);
}

int	get_c(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr)
		return(1);
	img->ceiling[0] = ft_atol(tmp_arr[0]);
	img->ceiling[1] = ft_atol(tmp_arr[1]);
	img->ceiling[2] = ft_atol(tmp_arr[2]);
	free_arr(&tmp_arr);
	if (range_check(img->ceiling))
	{
		err_msg(9);
		free_str(&img->no);
		return (1);
	}
	return (0);
}
int	get_f(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr)
		return(1);
	img->floor[0] = ft_atol(tmp_arr[0]);
	img->floor[1] = ft_atol(tmp_arr[1]);
	img->floor[2] = ft_atol(tmp_arr[2]);
	free_arr(&tmp_arr);
	if (range_check(img->floor))
	{
		err_msg(9);
		free_str(&img->no);
		return (1);
	}
	return (0);
}

int	range_check(long int *arr)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (arr[i] < 0 || arr[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

// void	check_null(t_img *img)
// {
// 	if((img->no == NULL) || (img->so == NULL) || 
// 	(img->ea == NULL) || (img->we == NULL))	
// 	{
// 		print_arr(img->data->file_arr);
// 		// free_arr(&img->data->file_arr);
// 		printf("TEST HERE!\n");	
// 		free_arr(&img->data->map);
// 		free_str(&img->data->file_cnt);
// 		free_str(&img->no);
// 		free_str(&img->ea);
// 		free_str(&img->so);
// 		free_str(&img->we);
// 		printf("caught a null!\n");
// 	}

// }
