/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/30 12:43:30 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;
	//mlx_t	mlx;

	if (argc == 2)
	{
		init_data (&data, &img);
		if (cube_it(argv[1], &data, &img))
			return (1);
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
