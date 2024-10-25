/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/25 17:54:27 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int f_abs(int n)
{ 
	return ((n > 0) ? n : (n * (-1)));
}
 
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
	steps_n = f_abs(dx) > f_abs(dy) ? f_abs(dx) : f_abs(dy);
	x_inc = dx / (float)steps_n;
	y_inc = dy / (float)steps_n;

	while (i <= steps_n)
	{
		mlx_put_pixel(data->img->ray, x, y,  0xFF0000FF);
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
}

static void	init_hor_inter_values(t_data *data)
{
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->ray_or = data->p_a;
	data->hor_dis = 0;
	data->hor_hit = 0;
}

void	check_closest_hor_inter(t_data *data)
{
	init_hor_inter_values(data);
	// if (data->ray_or != PI && data->ray_or != 2 * PI)
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
		data->hor_dis = sqrt((data->hor_next_x - data->x_p) * (data->hor_next_x - data->x_p)
			+ (data->hor_next_y - data->y_p) * (data->hor_next_y - data->y_p));
	}
	else
		data->hor_dis = 12345678;
	printf("close_hor_x %f\n", data->hor_next_x);
	printf("close_hor_y %f\n", data->hor_next_y);
	// if (data->map[(int)(data->hor_next_y)][(int)(data->hor_next_x)] == '1')
	// 	data->hor_hit = 1;
	if (data->hor_next_x > 0 && data->hor_next_y > 0 && data->hor_next_x < S_WID && data->hor_next_y < S_HEI)
		draw_ray_test(data, data->x_p * data->PX, data->y_p * data->PX, data->hor_next_x * data->PX, data->PX * data->hor_next_y);
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
		data->ver_dis = sqrt((data->ver_next_x - data->x_p) * (data->ver_next_x - data->x_p)
			+ (data->ver_next_y - data->y_p) * (data->ver_next_y - data->y_p));
	}
	else
		data->ver_dis = 12345678;
	printf("close_ver_x %f\n", data->ver_next_x);
	printf("close_ver_y %f\n", data->ver_next_y);
	// if (data->map[(int)(data->ver_next_y)][(int)(data->ver_next_x)] == '1')
	// 	data->ver_hit = 1;
	if (data->ver_next_x > 0 && data->ver_next_y > 0 && data->ver_next_x < S_WID && data->ver_next_y < S_HEI)
		draw_ray_test(data, data->x_p * data->PX, data->y_p * data->PX, data->ver_next_x * data->PX, data->PX * data->ver_next_y);
}

static void	init_fnl_cord(t_data *data)
{
	data->cl_y = 0;
	data->cl_x = 0;
	data->cl_dis = 0;
}

// static void	comp_closest_inter(t_data *data)
// {
// 	if (data->ver_dis > data->hor_dis)
// 	{
// 		data->cl_y = data->hor_next_y;
// 		data->cl_x = data->hor_next_x;
// 		data->cl_dis = data->hor_dis;
// 	}
// 	else
// 	{
// 		data->cl_y = data->ver_next_y;
// 		data->cl_x = data->ver_next_x;
// 		data->cl_dis = data->ver_dis;
// 	}
// 	if (data->cl_x > 0 && data->cl_y > 0 && data->cl_x < S_WID && data->cl_y < S_HEI)
// 		draw_ray_test(data, data->x_p * data->PX, data->y_p * data->PX, data->cl_x * data->PX, data->PX * data->cl_y);		
// }

void	raycaster(t_data *data)
{
	init_fnl_cord(data);
	check_closest_hor_inter(data);
	check_closest_hor_inter(data);
	// if (data->hor_hit || data->ver_hit)
	// 	comp_closest_inter(data);
}