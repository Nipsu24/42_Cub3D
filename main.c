/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 10:34:57 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		data	data;
		img 	img;

		(void)img;
		
		init_data (&data);
		cube_it(argv[1], &data);
		//printf("%s \n\n\n END OF FILE", data.file_cnt);
	}
	else
		printf("incorrect argument\n");
}
