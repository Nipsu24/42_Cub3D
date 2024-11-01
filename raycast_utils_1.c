/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:41:17 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 14:03:28 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Function for calculating the distance between 2 points in a grid*/
float	calc_dist(float x, float y, float x_tar, float y_tar)
{
	float	dist;

	dist = 0;
	dist = sqrt((x_tar - x) * (x_tar - x) + (y_tar - y) * (y_tar - y));
	return (dist);
}

/*Gives out ray length of shorter ray retrieved from the
  vertical/horizontal intersection check. Also sets value 
  of hit_dir, depending on which site of a grid field has
  been hit by the ray (N,E,S,W - 1,2,3,4)*/
float	calc_ray_len(t_data *data)
{
	if (data->ver_dis > data->hor_dis)
	{
		data->cl_x = data->hor_next_x;
		data->cl_y = data->hor_next_y;
		if (data->ray_or > PI)
			data->hit_dir = 3;
		else
			data->hit_dir = 1;
	}
	else
	{
		data->cl_x = data->ver_next_x;
		data->cl_y = data->ver_next_y;
		if (data->ray_or < PI / 2 || data->ray_or > 3 * PI / 2)
			data->hit_dir = 2;
		else
			data->hit_dir = 4;
	}
	return (calc_dist(data->x_p, data->y_p, data->cl_x, data->cl_y));
}

/*Accounts for potential "overspin" of the ray angles
  (used in raycaster/set_up_intersec_check function)*/
void	normalize_angle(float *angle_1, float *angle_2)
{
	if (*angle_1 < 0)
	{
		*angle_1 += 2 * PI;
		*angle_2 += 2 * PI;
	}
	else if (*angle_1 > 2 * PI)
	{
		*angle_1 -= 2 * PI;
		*angle_2 -= 2 * PI;
	}
}
