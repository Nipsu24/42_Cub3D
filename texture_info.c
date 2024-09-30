/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:13:57 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/30 11:20:43 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_extract(t_data *data, t_img *img, int i, int j)
{
	while(data->file_arr[++j])
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
	}
	// check_null(img);
}

void get_c(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	img->ceiling[0] = ft_atoi(tmp_arr[0]);
	img->ceiling[1] = ft_atoi(tmp_arr[1]);
	img->ceiling[2] = ft_atoi(tmp_arr[2]);
	free_arr(&tmp_arr);
	if (range_check(img->ceiling))
		img->no = NULL;
}
void get_f(char *address, t_img *img)
{
	char **tmp_arr;

	address++;
	tmp_arr = ft_split(address, ',');
	img->floor[0] = ft_atoi(tmp_arr[0]);
	img->floor[1] = ft_atoi(tmp_arr[1]);
	img->floor[2] = ft_atoi(tmp_arr[2]);
	free_arr(&tmp_arr);
	if (range_check(img->ceiling))
		img->no = NULL;
}

int	range_check(int *arr)
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
