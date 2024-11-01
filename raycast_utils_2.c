/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:39:00 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 12:25:20 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int	calc_tar_dist(float coord, float tar_coord)
{
	float	dist;

	dist = tar_coord - coord;
	return (dist);
}

static int calc_step_size(float dx, float dy)
{
	int	steps;

	steps = 0;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	return (steps);
}

static void	init_draw_ray(t_data *data, t_ray *ray)
{
	ray->dx = 0;
	ray->dy = 0;
	ray->steps = 0;
	ray->x_inc = 0;
	ray->y_inc = 0;
	ray->j = 0;
	ray->x = 0;
	ray->y = 0;

	ray->dx = calc_tar_dist(data->x_p * data->PX, data->cl_x * data->PX);
	ray->dy = calc_tar_dist(data->y_p * data->PX, data->cl_y * data->PX);
	ray->steps = calc_step_size(ray->dx, ray->dy);
	ray->x_inc = ray->dx / (float)ray->steps;
	ray->y_inc = ray->dy / (float)ray->steps;
	ray->x = data->x_p;
	ray->y = data->y_p;
	ray->x *= data->PX;
	ray->y *= data->PX;
}

void	draw_ray(t_data *data, int i)
{
	init_draw_ray(data, data->ray);
	if (data->cl_y >= 0 && data->cl_y < data->height
			&& data->cl_x >= 0 && data->cl_x < data->width
			&& i % RAYS_MODULO == 0)
	{	
		while (data->ray->j <= data->ray->steps)
		{
			mlx_put_pixel(data->img->ray,
				(int)(data->ray->x), (int)(data->ray->y), 0xFF0000FF);
			data->ray->x += data->ray->x_inc;
			data->ray->y += data->ray->y_inc;
			data->ray->j++;
		}
	}
}
