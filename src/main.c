/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/07 15:12:34 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		exit (1);
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
}

// static void init_player(t_data *data)
// {
// 	data->txtr = malloc(sizeof(t_player));
// 	if (!data->player)
// 	{
// 		free(data->img);
// 		free(data->txtr);
// 		data->img = NULL;
// 		exit (1);
// 	}
// }

/*Initialises variables of the main data struct.*/
static void	init_structs(t_data *data)
{
	init_img(data);
	init_txtr(data);
	// init_player(data);
	data->txtr->wl = NULL;
	data->txtr->fl = NULL;
	data->txtr->pl = NULL;
	data->img->wl = NULL;
	data->img->fl = NULL;
	data->img->pl = NULL;
	data->img->ray = NULL;
	data->img->data = data;
	data->map = NULL;
	data->clone_map = NULL;
	data->file_cnt = NULL;
	data->file_arr = NULL;
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
	data->wall_check = 0;
	data->p_dir = 'F';
	data->x_p = 0;
	data->y_p = 0;
	data->ray_dir_x = 0;
	data->ray_dir_y= 0;
	data->mlx = NULL;
	data->height = 0;
	data->width = 0;
	data->parsing_ok = 0;
	// data->player->dir_x = 0;
	// data->player->dir_y = 0;
	// data->player->plane_x = 0;
	// data->player->plane_y = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_structs(&data);
		if (cube_it(argv[1], &data, data.img))
			return (free_all(&data, 1));
		printf("SUCCESS\n");
		return (free_all(&data, 0));
	}
	else
	{
		printf("Error\nincorrect argument\n");
		sleep(1);
		printf(".....\n");
		sleep(2);
		printf("you idiot\n");
		sleep(2);
	}
	return (0);
}
