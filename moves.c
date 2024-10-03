/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/03 17:05:41 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	move_up(t_data *data)
{
	if (data->map[data->img->pl->instances->y / PX - 1]
		[data->img->pl->instances->x / PX] != '1')
	{
		data->img->pl->instances->y -= PX/10;
		data->y_p -= 1;
	}
}

void	move_left(t_data *data)
{
	if (data->map[data->img->pl->instances->y / PX]
		[data->img->pl->instances->x / PX - 1] != '1')
	{
		data->img->pl->instances->x -= PX/10;
		data->x_p -= 1;
	}
}

void	move_down(t_data *data)
{
	if (data->map[data->img->pl->instances->y / PX + 1]
		[data->img->pl->instances->x / PX] != '1')
	{
		data->img->pl->instances->y += PX/10;
		data->y_p += 1;
	}
}

void	move_right(t_data *data)
{
	if (data->map[data->img->pl->instances->y / PX]
		[data->img->pl->instances->x / PX + 1] != '1')
	{
		data->img->pl->instances->x += PX/10;
		data->x_p += 1;
	}
}
