/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:15 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/03 16:09:54 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Frees all relevant data allocated for the project. Returns 1
  if return val is set to 1. If set to 0, returns 0.*/
int	free_all(t_data *data, int return_val)
{
	free_input(data);
	free_dir(data->img);
	free(data->img);
	data->img = NULL;
	free(data->txtr);
	data->txtr = NULL;
	if (data->parsing_ok)
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
	}
	if (return_val)
		return (1);
	else
		return (0);
}

/*Frees related input variables in case map parameters
  are invalid. Quits with 1.*/
int	free_input(t_data *data)
{
	free_arr(&data->map);
	free_str(&data->file_cnt);
	free_arr(&data->file_arr);
	return (1);
}

int	free_dir(t_img *img)
{
	free_str(&img->no);
	free_str(&img->ea);
	free_str(&img->we);
	free_str(&img->so);
	return (1);
}
