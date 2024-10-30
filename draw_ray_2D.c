/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_2D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:57:09 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/25 13:59:10 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
static void	draw_single_ray(t_data *data, float angle, int color)
{
	float	x;
	float	y;
	float	mag;

	x = (data->x_p * data->PX) + (data->pl_size / 2);
	y = (data->y_p * data->PX) + (data->pl_size / 2);
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * RAY_SPEED * data->PX);
		y += (data->ray_dir_y * RAY_SPEED * data->PX);
		if (x < 0 || y < 0 || x >= data->width * data->PX || y >= data->height * data->PX
			|| data->map[(int)y / (int)data->PX][(int)x / (int)data->PX] == '1')
			break ;
		mlx_put_pixel(data->img->ray, x, y, color);
	}
}

void	draw_fov(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	current_angle;
	float	step_angle;

	data->ray_index = 0;
	start_angle = data->p_a - PI / 6;
	end_angle = data->p_a + PI / 6;
	step_angle = (end_angle - start_angle) / MM_RAYS;
	current_angle = start_angle;
	data->img->colour = 0xFF0000FF;
	while (current_angle <= end_angle)
	{
		draw_single_ray(data, current_angle, data->img->colour);
		current_angle += step_angle;
		data->ray_index++;
		if (data->img->colour == 0xFF0000FF)
			data->img->colour = 0x00FF00FF;
		else if (data->img->colour == 0x00FF00FF)
			data->img->colour = 0x0000FFFF;
		else
			data->img->colour = 0xFF0000FF;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
