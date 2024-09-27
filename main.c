/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/26 14:34:58 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_data	data;
		t_img 	img;

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
