/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/16 12:00:21 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	create_ray_img(t_data *data)
{
	data->img->ray = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->ray)
		return (1);
	return (0);
}

int	create_pl_img(t_data *data)
{
	data->img->pl = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->pl)
		return (1);
	return (0);
}

/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
void	draw_single_ray(t_data *data, float angle, int color)
{
	float	x;
	float	y;
	float	mag;

	x = (data->x_p * PX) + PXP / 2;
	y = (data->y_p * PX) + PXP / 2;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * ray_speed * PX);
		y += (data->ray_dir_y * ray_speed * PX);
		if (x < 0 || y < 0 || x >= data->width * PX || y >= data->height * PX
			|| data->map[(int)y / PX][(int)x / PX] == '1')
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

	start_angle = data->p_a - PI / 4;
	end_angle = data->p_a + PI / 4;
	step_angle = (end_angle - start_angle) / rays;
	current_angle = start_angle;
	data->img->colour = 0xFF0000FF;
	while (current_angle <= end_angle)
	{
		draw_single_ray(data, current_angle, data->img->colour);
		current_angle += step_angle;
		if (data->img->colour == 0xFF0000FF)
			data->img->colour = 0x00FF00FF;
		else if (data->img->colour == 0x00FF00FF)
			data->img->colour = 0x0000FFFF;
		else
			data->img->colour = 0xFF0000FF;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
