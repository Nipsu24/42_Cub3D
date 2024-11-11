/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:55 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/11 10:46:25 by lstorey          ###   ########.fr       */
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
		return (free_all(&data, 0));
	}
	else
		official_exit();
	return (0);
}
