/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:02:43 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 14:59:23 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Checks for wall or boundary collision and returns for those cases 1.*/
static int	hit_check(t_data *data, float x, float y)
{
	if (y < 0 || y >= data->height || x < 0 || x >= data->width)
		return (1);
	if (data->map[(int)((y))][(int)((x))] == '1')
		return (1);
	return (0);
}

/*Passes identified horizontal intersection values to hit_check function
  which returns 1 in case a hit is detected. Y values with orientation
  to North need to be substracted by one so that ray does not leap over
  wall field and only stops then.*/
static void	check_horizontal_hit(t_data *data)
{
	if (data->ray_or > PI)
	{
		if (hit_check(data, data->hor_next_x, data->hor_next_y))
			data->hor_hit = 1;
	}
	else
	{
		if (hit_check(data, data->hor_next_x, data->hor_next_y - 1))
			data->hor_hit = 1;
	}
	data->hor_dis = calc_dist(data->x_p, data->y_p,
			data->hor_next_x, data->hor_next_y);
}

/*Passes identified vertical intersection values to hit_check function
  which returns 1 in case a hit is detected. X values with orientation
  to left need to be substracted by one so that ray does not leap over
  wall field and only stops then.*/
static void	check_vertical_hit(t_data *data)
{
	if (data->ray_or < PI / 2 || data->ray_or > 3 * PI / 2)
	{
		if (hit_check(data, data->ver_next_x, data->ver_next_y))
			data->ver_hit = 1;
	}
	else
	{
		if (hit_check(data, data->ver_next_x - 1, data->ver_next_y))
			data->ver_hit = 1;
	}
	data->ver_dis = calc_dist(data->x_p, data->y_p,
			data->ver_next_x, data->ver_next_y);
}

/*Contains relevant functions for hit wall detection.*/
void	ft_hit_wall(t_data *data)
{
	check_horizontal_hit(data);
	check_vertical_hit(data);
}
