/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:08:05 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/30 15:09:32 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	check_closest_hor_inter(t_data *data)
{
	if (!(fabs(data->ray_or - PI) < EPSILON) && !(fabs(data->ray_or - 2 * PI) < EPSILON))
	{
		if (data->ray_or > PI) // y values increase (moving South)
		{
			data->hor_next_y = ceilf(data->y_p); //calculates closest int upwards
			data->hor_next_x = data->x_p + (data->hor_next_y - data->y_p) / -tan(data->ray_or);
		}
		else // y values decrease (moving North)
		{
			data->hor_next_y = floorf(data->y_p); //calculates closest int downwards
			data->hor_next_x = data->x_p + (data->y_p - data->hor_next_y) / tan(data->ray_or);
		}
	}
	else
	{
		data->hor_dis = 12345678;
		data->hor_hit = 1;
	}
}

void	check_closest_ver_inter(t_data *data)
{
	if (!(fabs(data->ray_or - PI / 2) < EPSILON) && !(fabs(data->ray_or - 3 * PI / 2) < EPSILON))
	{
		if (data->ray_or < PI/2 || data->ray_or > 3 * PI / 2) // x values increase (moving right)
		{
			data->ver_next_x = ceilf(data->x_p); //calculates closest int to the right
			data->ver_next_y = data->y_p + (data->ver_next_x - data->x_p) * -tan(data->ray_or);
		}
		else // x values decrease (moving left)
		{
			data->ver_next_x = floorf(data->x_p); //calculates closest int to the left
			data->ver_next_y = data->y_p + (data->x_p - data->ver_next_x) * tan(data->ray_or);
		}
	}
	else
	{
		data->ver_dis = 12345678;
		data->ver_hit = 1;
	}
}

void	calc_delta_hor(t_data *data)
{
	// Determine step size for y
	if (data->ray_or > PI)
		// Moving South (downward)
		data->hor_y_step = 1; // moving down to the next horizontal line
	else
		// Moving North (upward)
		data->hor_y_step = -1; // moving up to the previous horizontal line
	// Calculate the x step size based on the ray angle
	if (data->hor_y_step == 1)
		data->hor_x_step = 1 / -tan(data->ray_or);
	else
		data->hor_x_step = 1 / tan(data->ray_or);
}

void	calc_delta_ver(t_data *data)
{
	// Determine step size for x
	if (data->ray_or < PI / 2 || data->ray_or > 3 * PI / 2)
		// Moving right
		data->ver_x_step = 1; // moving to the next vertical line to the right
	else
		// Moving left
		data->ver_x_step = -1; // moving to the next vertical line to the left
	// Calculate the y step size based on the ray angle
	if (data->ver_x_step == 1)
		data->ver_y_step = (1 * -tan(data->ray_or)); // positive y step for rightward ray
	else
		data->ver_y_step = (1 * tan(data->ray_or)); // negative y step for leftward ray
}
