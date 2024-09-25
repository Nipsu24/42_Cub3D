/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/25 13:24:15 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		data	data;
		img 	img;

		init_data (&data, &img);
		if (cube_it(argv[1], &data, &img))
			return (1);
	}
	else
		printf("incorrect argument\n");
}
