/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/03 10:51:27 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		exit (1);
}

/*Initialises variables of the main data struct.*/
static void	init_structs(t_data *data)
{
	init_img(data);
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
	data->x_p = 0;
	data->y_p = 0;
	data->mlx = NULL;
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
