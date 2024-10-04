/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/04 17:22:28 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	move_up(t_data *data)
{
	float	new_y;

	new_y = data->img->pl->instances->y - PX / steps;
	if (data->map[(int)((new_y - col_buf) / PX)]
		[(int)((data->img->pl->instances->x + pl_img_size / 2) / PX)] != '1')
	{
		data->img->pl->instances->y = new_y;
		data->y_p -= 1;
	}
}

void	move_down(t_data *data)
{
	float	new_y;

	new_y = data->img->pl->instances->y + PX / steps;
	if (data->map[(int)((new_y + pl_img_size + col_buf) / PX)]
		[(int)((data->img->pl->instances->x + pl_img_size / 2) / PX)] != '1')
	{
		data->img->pl->instances->y = new_y;
		data->y_p += 1;
	}
}

void	move_left(t_data *data)
{
	float	new_x;

	new_x = data->img->pl->instances->x - PX / steps;
	if (data->map[(int)((data->img->pl->instances->y + pl_img_size / 2) / PX)]
		[(int)((new_x - col_buf) / PX)] != '1')
	{
		data->img->pl->instances->x = new_x;
		data->x_p -= 1;
	}
}

void	move_right(t_data *data)
{
	float	new_x;

	new_x = data->img->pl->instances->x + PX / steps;
	if (data->map[(int)((data->img->pl->instances->y + pl_img_size / 2) / PX)]
		[(int)((new_x + pl_img_size + col_buf) / PX)] != '1')
	{
		data->img->pl->instances->x = new_x;
		data->x_p += 1;
	}
}
