/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/31 11:31:56 by mmeier           ###   ########.fr       */
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
	data->img->wl = NULL;
	data->img->fl = NULL;
	data->img->pl = NULL;
	data->img->bg = NULL;
	data->img->fg = NULL;
	data->img->ray = NULL;
	data->img->bg_ray = NULL;
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
	data->txtr->pl = NULL;
}

/*Initialises variables of the main data struct.*/
static void	init_structs(t_data *data)
{
	init_img(data);
	init_txtr(data);
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
	data->ray_dist = 0;
	data->line_height = 0;
	data->ray_index = 0;
	data->PX = 0;
	data->pl_size = 0;
	data->dist_plane = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_structs(&data);
		if (cube_it(argv[1], &data))
			return (free_all(&data, 1));
		printf("SUCCESS\n");
		return (free_all(&data, 0));
	}
	else
		official_exit();
	return (0);
}
