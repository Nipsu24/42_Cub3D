/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/02 10:38:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Initialises variables of the main data struct.*/
static void	init_data(t_data *data, t_img *img)
{
	data->map = NULL;
	data->clone_map = NULL;
	data->file_cnt = NULL;
	data->file_arr = NULL;
	img->no = NULL;
	img->so = NULL;
	img->ea = NULL;
	img->we = NULL;
	img->ceiling[0] = -1;
	img->ceiling[1] = -1;
	img->ceiling[2] = -1;
	img->floor[0] = -1;
	img->floor[1] = -1;
	img->floor[2] = -1;
	data->wall_check = 0;
	data->x_p = 0;
	data->y_p = 0;
	data->mlx = NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	if (argc == 2)
	{
		init_data (&data, &img);
		if (cube_it(argv[1], &data, &img))
			return (free_all(&data, &img, 1));
		printf("SUCCESS\n");
		return (free_all(&data, &img, 0));
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
