/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/26 17:43:38 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void get_north(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->no = ft_substr(address, i, ft_strlen(address) - i);
}

static void get_east(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->ea = ft_substr(address, i, ft_strlen(address) - i);
}

static void get_south(char *address, t_img *img)
{
	int i;
	
	i = 2;
	while (address[i] == ' ')
		i++;
	img->so = ft_substr(address, i, ft_strlen(address) - i);
}

static void get_west(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->we = ft_substr(address, i, ft_strlen(address) - i);
}

static void get_c(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	img->ceiling[0] = ft_atoi(tmp_arr[0]);
	img->ceiling[1] = ft_atoi(tmp_arr[1]);
	img->ceiling[2] = ft_atoi(tmp_arr[2]);
	free_arr(&tmp_arr);
}
static void get_f(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	img->floor[0] = ft_atoi(tmp_arr[0]);
	img->floor[1] = ft_atoi(tmp_arr[1]);
	img->floor[2] = ft_atoi(tmp_arr[2]);
	free_arr(&tmp_arr);
}

void	texture_extract(t_data *data, t_img *img, int i, int j)
{
	while(data->file_arr[j])
	{
		while (data->file_arr[j][i])
		{
			if ((ft_strncmp("NO ", &data->file_arr[j][i], 3) == 0) || 
			(ft_strncmp("EA ", &data->file_arr[j][i], 3) == 0) || 
			(ft_strncmp("SO ", &data->file_arr[j][i], 3) == 0) || 
			(ft_strncmp("WE ", &data->file_arr[j][i], 3) == 0) || 
			(ft_strncmp("F ", &data->file_arr[j][i], 2) == 0) ||
			(ft_strncmp("C ", &data->file_arr[j][i], 2) == 0))
			{
				if (ft_strncmp("NO ", &data->file_arr[j][i], 3) == 0)
					get_north(&data->file_arr[j][i], img);
				else if(ft_strncmp("EA ", &data->file_arr[j][i], 3) == 0)
					get_east(&data->file_arr[j][i], img);
				else if (ft_strncmp("SO ", &data->file_arr[j][i], 3) == 0)
					get_south(&data->file_arr[j][i], img);
				else if (ft_strncmp("WE ", &data->file_arr[j][i], 3) == 0)
					get_west(&data->file_arr[j][i], img);
				else if (ft_strncmp("C ", &data->file_arr[j][i], 2) == 0)
					get_c(&data->file_arr[j][i], img);
				else if (ft_strncmp("F ", &data->file_arr[j][i], 2) == 0)
					get_f(&data->file_arr[j][i], img);
			}
			break;		
		}
		j++;
	}
}
/*	DUMP TO BE DELETED*/
/*
static void get_c(char *address, img *img)
{
	int i;

	i = 1;
	while (address[i] == ' ')
		i++;
	img->ceiling[0] = ft_atoi(&address[i]);
	printf("img->ceiling[0]:%i\n", img->ceiling[0]);
	i++;
	i++;
	i++;
	while (address[i] == ' ' || address[i] == ',')
		i++;
	img->ceiling[1] = ft_atoi(&address[i]);
	printf("img->ceiling[1]:%i\n", img->ceiling[1]);
	i++;
	while (address[i] == ' ' || address[i] == ',')
		i++;
	img->ceiling[2] = ft_atoi(&address[i]);
	printf("img->ceiling[2]:%i\n", img->ceiling[2]);
}
*/
