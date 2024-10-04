/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/04 12:57:57 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	move_up(t_data *data)
{
    float new_y;

	new_y = data->img->pl->instances->y - PX / 10;
    if (data->map[(int)(new_y / PX)][(int)(data->img->pl->instances->x / PX)] != '1')
    {
        data->img->pl->instances->y = new_y;
        data->y_p -= 1;
    }
}

// void	move_up(t_data *data)
// {
// 	if (data->map[data->img->pl->instances->y / PX - 1]
// 		[data->img->pl->instances->x / PX] != '1')
// 	{
// 		data->img->pl->instances->y -= PX/10;
// 		data->y_p -= 1;
// 	}
// }

void	move_down(t_data *data)
{
	float new_y;
	
	new_y = data->img->pl->instances->y + PX / 10;
	if (data->map[(int)(new_y / PX)][(int)(data->img->pl->instances->x / PX)] != '1')
	{
		data->img->pl->instances->y = new_y;
		data->y_p += 1;
	}
}

void	move_left(t_data *data)
{
	float new_x;
	
	new_x = data->img->pl->instances->x - PX / 10;
	if (data->map[(int)(data->img->pl->instances->y / PX)][(int)(new_x / PX)] != '1')
	{
		data->img->pl->instances->x = new_x;
		data->x_p -= 1;
	}
}

void	move_right(t_data *data)
{
	float new_x;
	
	new_x = data->img->pl->instances->x + PX / 10;
	if (data->map[(int)(data->img->pl->instances->y / PX)][(int)(new_x / PX)] != '1')
	{
		data->img->pl->instances->x = new_x;
		data->x_p += 1;
	}
}
