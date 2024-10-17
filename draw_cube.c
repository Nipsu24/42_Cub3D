/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:26:24 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/17 16:26:27 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int f_abs(int n)
{ 
	return ((n > 0) ? n : (n * (-1)));
}
 
static void	draw_ray(t_data *data, float x, float y, float x_tar, float y_tar)
{
	float	dx;
	float	dy;
	int		steps_n;
	float	x_inc;
	float	y_inc;
	int		i;

	x = x * PX + PXP / 2;
	y = y * PX + PXP / 2;
	x_tar = x_tar * PX + PXP / 2;
	y_tar = y_tar * PX + PXP / 2;
	i = 0;
	dx = x_tar - x;
	dy = y_tar - y;
	steps_n = f_abs(dx) > f_abs(dy) ? f_abs(dx) : f_abs(dy);
	x_inc = dx / (float)steps_n;
	y_inc = dy / (float)steps_n;

	while (i <= steps_n)
	{
		mlx_put_pixel(data->img->bg_ray, x, y,  0xFF0000FF);
		x += x_inc;
		y += y_inc;
		i++;
	}
	mlx_image_to_window(data->mlx, data->img->bg_ray, 0, 0);
}

int	create_bg_ray_img(t_data *data)
{
	data->img->bg_ray = mlx_new_image(data->mlx,
			screen_width * PX, screen_height * PX);
	if (!data->img->bg_ray)
		return (1);
	return (0);
}

void	calc_line_height(t_data *data, float x, float y)
{
	float	start_y;
	float	end_y;
	float	ray_x_pos;
	
	data->ray_dist = sqrt((data->x_p - x) * (data->x_p - x)
				+ (data->y_p - y) * (data->y_p - y));
	data->line_height = (PX * screen_height) / data->ray_dist;
	if (data->line_height > screen_height)
		data->line_height = screen_height;
	start_y = (screen_height / 2) - (data->line_height /  2);
	if (start_y < 0)
		start_y = 0;
	end_y = start_y + data->height;
	if (end_y > screen_height)
		end_y = screen_height;
	ray_x_pos = (data->ray_index / (float)mm_rays) * screen_width;
	draw_ray(data, ray_x_pos, ray_x_pos, start_y, end_y);
}
