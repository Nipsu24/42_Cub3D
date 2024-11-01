/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:08:05 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 15:20:02 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Checks the closest horizontal intersection from the position
  of the player. EPSILON (EPS) value needed (close to 0) to offset float
  inaccurancy when setting values equal to PI. First if statement checks
  if ray is completely horizontal. If this is the case, jumps to 2nd else
  statement and sets "max" value for hor_dis, as ray will never hit a
  horizontal intersection. If ray faces south, rounds next y value up with
  ceilf function, otherwise floorf function used for rounding down
  (facing north). Uses -tan and tan division for determining related x value. */
void	check_closest_hor_inter(t_data *data)
{
	if (!(fabs(data->ray_or - PI) < EPS) && !(fabs(data->ray_or - 2 * PI) < EPS))
	{
		if (data->ray_or > PI)
		{
			data->hor_next_y = ceilf(data->y_p);
			data->hor_next_x = data->x_p + (data->hor_next_y - data->y_p) / -tan(data->ray_or);
		}
		else
		{
			data->hor_next_y = floorf(data->y_p);
			data->hor_next_x = data->x_p + (data->y_p - data->hor_next_y) / tan(data->ray_or);
		}
	}
	else
	{
		data->hor_dis = 12345678;
		data->hor_hit = 1;
	}
}

/*Checks the closest vertical intersection from the position
  of the player. EPSILON (EPS) value needed (close to 0) to offset float
  inaccurancy when setting values equal to PI. First if statement checks
  if ray is completely vertical. If this is the case, jumps to 2nd else
  statement and sets "max" value for ver_dis, as ray will never hit a
  vertical intersection. If ray faces east, rounds next x value up with
  ceilf function, otherwise floorf function used for rounding down
  (facing west). Uses -tan and tan multiplication for determining
  related y value. */
void	check_closest_ver_inter(t_data *data)
{
	if (!(fabs(data->ray_or - PI / 2) < EPS) && !(fabs(data->ray_or - 3 * PI / 2) < EPS))
	{
		if (data->ray_or < PI/2 || data->ray_or > 3 * PI / 2)
		{
			data->ver_next_x = ceilf(data->x_p);
			data->ver_next_y = data->y_p + (data->ver_next_x - data->x_p) * -tan(data->ray_or);
		}
		else
		{
			data->ver_next_x = floorf(data->x_p);
			data->ver_next_y = data->y_p + (data->x_p - data->ver_next_x) * tan(data->ray_or);
		}
	}
	else
	{
		data->ver_dis = 12345678;
		data->ver_hit = 1;
	}
}

/*Calculates the step size to be added after each horizontal intersection
  check. If facing south, y + 1, otherwise -1. Devision by tan and -tan
  used in order to determine relative x step value.*/
void	calc_delta_hor(t_data *data)
{
	if (data->ray_or > PI)
		data->hor_y_step = 1;
	else
		data->hor_y_step = -1;
	if (data->hor_y_step == 1)
		data->hor_x_step = 1 / -tan(data->ray_or);
	else
		data->hor_x_step = 1 / tan(data->ray_or);
}

/*Calculates the step size to be added after each vertical intersection
  check. If facing right, x + 1, otherwise -1. Multiplication by tan 
  and -tan used in order to determine relative y step value.*/
void	calc_delta_ver(t_data *data)
{
	if (data->ray_or < PI / 2 || data->ray_or > 3 * PI / 2)
		data->ver_x_step = 1;
	else
		data->ver_x_step = -1;
	if (data->ver_x_step == 1)
		data->ver_y_step = (1 * -tan(data->ray_or));
	else
		data->ver_y_step = (1 * tan(data->ray_or));
}
