/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_be_deleted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/25 15:21:00 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*prints 2d array*/
void	print_arr(char **arr)
{
	int	j;
	
	j = -1;
	while (arr[++j])
		printf("%s\n", arr[j]);		
}

void info_printer(t_img *img)
{
	printf("img->no         :%s\n", img->no);
	printf("img->ea         :%s\n", img->ea);
	printf("img->so         :%s\n", img->so);
	printf("img->we         :%s\n", img->we);
	printf("img->ceiling[0] :%d\n", img->ceiling[0]);
	printf("img->ceiling[1] :%d\n", img->ceiling[1]);
	printf("img->ceiling[2] :%d\n", img->ceiling[2]);
	printf("img->floor[0]   :%d\n", img->floor[0]);
	printf("img->floor[1]   :%d\n", img->floor[1]);
	printf("img->floor[2]   :%d\n", img->floor[2]);
}

void arr_splitter(t_data *data)
{
	data->file_arr = ft_split(data->file_cnt, '\n');
	if (!data->file_arr)
		return ;
}

void	file_splitter(t_data *data)
{
	data->map = ft_split(data->file_cnt, '\n');
	if (!data->map)
		return ;
}