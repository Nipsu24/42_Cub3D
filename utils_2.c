/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:40:44 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/30 16:24:34 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Prints dedicated error message depending on err_flag
  passed to function and returns 1.*/
int	err_msg(int err_flag)
{
	if (err_flag == 0)
		printf("Error.\nEmpty line(s) in map.\n");
	if (err_flag == 1)
		printf("Error.\nMultiple similar players in map or no player at all.\n");
	if (err_flag == 2)
		printf("Error.\nInvalid characters in map.\n");
	if (err_flag == 3)
		printf("Error.\nPlayer not surrounded by walls.\n");
	if (err_flag == 4)
		printf("Error.\nFloor or ceiling colour out of range.\n");
	if (err_flag == 5)
		printf("Error.\nMalloc error.\n");
	if (err_flag == 6)
		printf("Error.\nInvalid '.cub' file\n");
	return (1);
}

int arr_splitter(t_data *data)
{
	static int i = 0;

	while(data->file_cnt[i])
	{
		if (data->file_cnt[i] == ' ' && data->file_cnt[i + 1] == '\n')
		{
			free_str(&data->file_cnt);
			err_msg(6);
			return (1);
		}	
		i++;
	}
	data->file_arr = ft_split(data->file_cnt, '\n');
	if (!data->file_arr)
		return (1);
	return (0);
}
