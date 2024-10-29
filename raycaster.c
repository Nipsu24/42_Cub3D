/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/29 16:09:08 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	draw_ray_test(t_data *data, float x, float y, float x_tar, float y_tar)
{
	float	dx;
	float	dy;
	int		steps_n;
	float	x_inc;
	float	y_inc;
	int		i;

	i = 0;
	dx = x_tar - x;
	dy = y_tar - y;
	steps_n = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
	x_inc = dx / (float)steps_n;
	y_inc = dy / (float)steps_n;
	while (i <= steps_n)
	{
		mlx_put_pixel(data->img->ray, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
		x += x_inc;
		y += y_inc;
		i++;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}

static void	init_draw_ray(t_data *data)
{
	data->ver_next_y = 0;
	data->ver_next_x = 0;
	data->ray_or = data->p_a; // still need to be adjusted depending on ray angle, not player direction
	data->ver_dis = 0;
	data->ver_hit = 0;
	data->ver_x_step = 0;
	data->ver_y_step = 0;
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->hor_dis = 0;
	data->hor_hit = 0;
	data->hor_y_step = 0;
	data->hor_x_step = 0;
	data->cl_y = 0;
	data->cl_x = 0;
	data->cl_dis = 0;
	data->ray_len = 0;
}

float	calc_dist(float x, float y, float x_tar, float y_tar)
{
	float	dist;
	
	dist = 0;
	dist = sqrt((x_tar - x) * (x_tar - x) + (y_tar - y) * (y_tar - y));
	return (dist);
	
}

static void	step_forward(t_data *data)
{
	if (!data->hor_hit)
	{
		data->hor_next_x += data->hor_x_step;
		data->hor_next_y += data->hor_y_step;
	}
	if (!data->ver_hit)
	{
		data->ver_next_x += data->ver_x_step;
		data->ver_next_y += data->ver_y_step;
	}
}

static float	calc_ray_len(t_data *data)
{
	if (data->ver_dis > data->hor_dis)
	{
		data->cl_x = data->hor_next_x;
		data->cl_y = data->hor_next_y;
	}
	else
	{
		data->cl_x = data->ver_next_x;
		data->cl_y = data->ver_next_y;
	}
	return(calc_dist(data->x_p, data->y_p, data->cl_x, data->cl_y));
}

void	raycaster(t_data *data)
{
	float	ray_len;
	
	ray_len = 0;
	init_draw_ray(data);
	check_closest_hor_inter(data);
	check_closest_ver_inter(data);
	calc_delta_ver(data);
	calc_delta_hor(data);
	while (1)
	{
		ft_hit_wall(data);
		step_forward(data);
		if (data->ver_hit && data->hor_hit)
			break;
	}
	ray_len = calc_ray_len(data); // can also be retrieved differently
	if (data->cl_y >= 0 && data->cl_y < data->height && data->cl_x >= 0 && data->cl_x < data->width)
		draw_ray_test(data, data->x_p * data->PX, data->y_p * data->PX, data->cl_x * data->PX, data->cl_y * data->PX);
}
