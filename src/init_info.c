/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:48:13 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/08 13:59:57 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	arr_to_null(float *arr, int len)
{
	static int	i = 0;

	while (i < len)
	{
		arr[i] = 0;
		i++;
	}
}

static void	init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		exit (1);
	arr_to_null(&data->img->len[S_WID], S_WID);
	arr_to_null(&data->img->hit_dir[S_WID], S_WID);
	arr_to_null(&data->img->cl_x[S_WID], S_WID);
	arr_to_null(&data->img->cl_y[S_WID], S_WID);
	data->img->wl = NULL;
	data->img->fl = NULL;
	data->img->bg = NULL;
	data->img->fg = NULL;
	data->img->ray = NULL;
	data->img->data = data;
	data->img->no = NULL;
	data->img->so = NULL;
	data->img->ea = NULL;
	data->img->we = NULL;
	data->img->ceiling[0] = -1;
	data->img->ceiling[1] = -1;
	data->img->ceiling[2] = -1;
	data->img->floor[0] = -1;
	data->img->floor[1] = -1;
	data->img->floor[2] = -1;
}

static void	init_txtr(t_data *data)
{
	data->txtr = malloc(sizeof(t_txtr));
	if (!data->txtr)
	{
		free(data->img);
		data->img = NULL;
		exit (1);
	}
	data->txtr->wl = NULL;
	data->txtr->fl = NULL;
	data->txtr->no = NULL;
	data->txtr->ea = NULL;
	data->txtr->so = NULL;
	data->txtr->we = NULL;
	data->hit_dir = 0;
	data->slice_height = 0;
	data->texture = NULL;
	data->fov = 0;
	data->txt_y_st = 0;
	data->txt_y = 0;
	data->txt_x = 0;
}

static void	init_ray(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
	{
		free(data->img);
		free(data->txtr);
		data->img = NULL;
		data->txtr = NULL;
		exit (1);
	}
	data->ray->dx = 0;
	data->ray->dy = 0;
	data->ray->steps = 0;
	data->ray->x_inc = 0;
	data->ray->y_inc = 0;
	data->ray->j = 0;
	data->ray->x = 0;
	data->ray->y = 0;
}

/*Initialises variables of the main data struct.*/
void	init_structs(t_data *data)
{
	init_img(data);
	init_txtr(data);
	init_ray(data);
	data->map = NULL;
	data->clone_map = NULL;
	data->file_cnt = NULL;
	data->file_arr = NULL;
	data->wall_check = 0;
	data->p_dir = 'F';
	data->x_p = 0;
	data->y_p = 0;
	data->ray_dir_x = 0;
	data->ray_dir_y = 0;
	data->mlx = NULL;
	data->height = 0;
	data->width = 0;
	data->parsing_ok = 0;
	data->p_dx = 0;
	data->p_dy = 0;
	data->p_a = 0;
	data->line_height = 0;
	data->ray_index = 0;
	data->px = 0;
	data->dist_plane = 0;
}
