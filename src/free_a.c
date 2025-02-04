/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:15 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/08 14:04:48 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Frees all relevant data allocated for the project. Returns 1
  if return val is set to 1. If set to 0, returns 0.*/
int	free_all(t_data *data, int return_val)
{
	free_input(data);
	free_dir(data->img);
	if (!data->parsing_ok)
		free_structs(data);
	if (data->parsing_ok)
	{
		delete_textures(data);
		delete_images(data);
		if (data->mlx)
			mlx_terminate(data->mlx);
		free_structs(data);
	}
	if (return_val)
		return (1);
	else
		return (0);
}

/*Frees data structs for which memory was allocated*/
void	free_structs(t_data *data)
{
	if (data->img != NULL)
	{
		free(data->img);
		data->img = NULL;
	}
	if (data->txtr != NULL)
	{
		free(data->txtr);
		data->txtr = NULL;
	}
	if (data->ray != NULL)
	{
		free(data->ray);
		data->ray = NULL;
	}
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

void	delete_textures(t_data *data)
{
	if (data->txtr)
	{
		if (data->txtr->wl)
			mlx_delete_texture(data->txtr->wl);
		if (data->txtr->fl)
			mlx_delete_texture(data->txtr->fl);
		if (data->txtr->no)
			mlx_delete_texture(data->txtr->no);
		if (data->txtr->ea)
			mlx_delete_texture(data->txtr->ea);
		if (data->txtr->so)
			mlx_delete_texture(data->txtr->so);
		if (data->txtr->we)
			mlx_delete_texture(data->txtr->we);
		free(data->txtr);
		data->txtr = NULL;
	}
}
