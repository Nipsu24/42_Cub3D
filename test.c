/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/28 16:57:38 by mmeier           ###   ########.fr       */
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

static void	init_ver_inter_values(t_data *data)
{
	data->ver_next_y = 0;
	data->ver_next_x = 0;
	data->ray_or = data->p_a; // still need to be adjusted depending on ray angle, not player direction
	data->ver_dis = 0;
	data->ver_hit = 0;
	data->ver_x_step = 0;
	data->ver_y_step = 0;
	data->ray_vertical = 0;
}

static void	init_hor_inter_values(t_data *data)
{
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->ray_or = data->p_a;
	data->hor_dis = 0;
	data->hor_hit = 0;
	data->hor_y_step = 0;
	data->hor_x_step = 0;
	data->ray_horizontal = 0;
}

void	check_closest_hor_inter(t_data *data)
{
	init_hor_inter_values(data);
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
		data->ray_horizontal = 1;
	}
	printf("close_hor_x %f\n", data->hor_next_x);
	printf("close_hor_y %f\n", data->hor_next_y);
}

void	check_closest_ver_inter(t_data *data)
{
	init_ver_inter_values(data);
	if (!(fabs(data->ray_or - PI/2) < EPSILON) && !(fabs(data->ray_or - 3 * PI/2) < EPSILON))
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
		data->ray_vertical = 1;
	}
	printf("close_ver_x %f\n", data->ver_next_x);
	printf("close_ver_y %f\n", data->ver_next_y);
}

static void	init_fnl_cord(t_data *data)
{
	data->cl_y = 0;
	data->cl_x = 0;
	data->cl_dis = 0;
}

static void	calc_delta_hor(t_data *data)
{
	// Determine step size for y
	if (!data->ray_horizontal)
	{
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
}

static void	calc_delta_ver(t_data *data)
{
    // if (!(fabs(data->ray_or - PI/2) < EPSILON) && !(fabs(data->ray_or - 3 * PI/2) < EPSILON))
	if (!data->ray_vertical)
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
}

void	raycaster(t_data *data)
{
	check_closest_hor_inter(data);
	check_closest_ver_inter(data);
	init_fnl_cord(data);
	calc_delta_ver(data);
	calc_delta_hor(data);
	while (1)
	{
		data->hor_hit = 0;
		data->ver_hit = 0;
		if (data->hor_next_y >= 0 && data->hor_next_y < data->height && data->hor_next_x >= 0 && data->hor_next_x < data->width && !data->ray_horizontal)
		{
			if (data->map[(int)(data->hor_next_y)][(int)(data->hor_next_x)] == '1')
			{
				data->hor_dis = sqrt((data->hor_next_x - data->x_p) * (data->hor_next_x - data->x_p)
					+ (data->hor_next_y - data->y_p) * (data->hor_next_y - data->y_p));
				data->hor_hit = 1;
			}
		}
		if (data->ver_next_y >= 0 && data->ver_next_y < data->height && data->ver_next_x >= 0 && data->ver_next_x < data->width && !data->ray_vertical)
		{
			if (data->map[(int)(data->ver_next_y)][(int)((data->ver_next_x))] == '1')
			{
				data->ver_dis = sqrt((data->ver_next_x - data->x_p) * (data->ver_next_x - data->x_p)
					+ (data->ver_next_y - data->y_p) * (data->ver_next_y - data->y_p));
				data->ver_hit = 1;
			}
		}
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
		if (data->ver_hit || data->hor_hit)
			break;
	}
	if (data->hor_hit && data->ver_hit)
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
	}
	else if (data->hor_hit && !data->ver_hit)
	{
		data->cl_x = data->hor_next_x;
		data->cl_y = data->hor_next_y;
	}
	else if (data->ver_hit && !data->hor_hit)
	{
		data->cl_x = data->ver_next_x;
		data->cl_y = data->ver_next_y;
	}
	if (data->cl_y >= 0 && data->cl_y < data->height && data->cl_x >= 0 && data->cl_x < data->width)
		draw_ray_test(data, data->x_p * data->PX, data->y_p * data->PX, data->cl_x * data->PX, data->cl_y * data->PX);
	// comp_closest_inter_fnl(data);
}
