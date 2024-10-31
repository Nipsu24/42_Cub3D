/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/31 14:06:09 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

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
