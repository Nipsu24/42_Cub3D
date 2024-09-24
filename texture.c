/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 15:02:03 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void get_north(char *address, img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->no = ft_substr(address, i, ft_strlen(address) - i);
	printf("img->no:%s\n", img->no);
}

static void get_east(char *address, img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->ea = ft_substr(address, i, ft_strlen(address) - i);
	printf("img->ea:%s\n", img->ea);
}

static void get_south(char *address, img *img)
{
	int i;
	
	i = 2;
	while (address[i] == ' ')
		i++;
	img->so = ft_substr(address, i, ft_strlen(address) - i);
	printf("img->so:%s\n", img->so);
}

static void get_west(char *address, img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->we = ft_substr(address, i, ft_strlen(address) - i);
	printf("img->we:%s\n", img->we);
}

void	texture_extract(data *data, img *img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(data->file_arr[j])
	{
		while (data->file_arr[j][i])
		{
			if (ft_strncmp("NO ", &data->file_arr[j][i], 3) == 0)
			{
				get_north(&data->file_arr[j][i], img);
				break;
			}
			if (ft_strncmp("EA ", &data->file_arr[j][i], 3) == 0)
			{
				get_east(&data->file_arr[j][i], img);
				break;
			}	
			if (ft_strncmp("SO ", &data->file_arr[j][i], 3) == 0)
			{
				get_south(&data->file_arr[j][i], img);
				break;
			}	
			if (ft_strncmp("WE ", &data->file_arr[j][i], 3) == 0)
			{
				get_west(&data->file_arr[j][i], img);
				break;
			}	
			if (ft_strncmp("C ", &data->file_arr[j][i], 2) == 0)
			{
				printf("C FOUND\n");
				break;
			}	
			if (ft_strncmp("F ", &data->file_arr[j][i], 2) == 0)
			{
				printf("F FOUND\n");
				break;
			}	
			break;
		}
		j++;
	}
}

