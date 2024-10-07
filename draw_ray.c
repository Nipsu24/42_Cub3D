/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/07 15:50:13 by mmeier           ###   ########.fr       */
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

/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player.*/
void	draw_line(t_data *data)
{
	int		x;
	int		y;
	float	magnitude;

	x = (int)(data->x_p * PX) + PXP / 2;
	y = (int)(data->y_p * PX) + PXP / 2;
	data->ray_dir_x = 0;
	data->ray_dir_y = 0;
	if (data->p_dir == 'N')
		data->ray_dir_y = -1;
	else if (data->p_dir == 'E')
		data->ray_dir_x = 1;
	else if (data->p_dir == 'S')
		data->ray_dir_y = 1;
	else if (data->p_dir == 'W')
		data->ray_dir_x = -1;
	magnitude = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= magnitude;
	data->ray_dir_y /= magnitude;
	while (1)
	{
		x += (int)(data->ray_dir_x * ray_speed * PX);
		y += (int)(data->ray_dir_y * ray_speed * PX);
		if (x < 0 || y < 0 || x >= data->width * PX || y >= data->height * PX
			|| data->map[y / PX][x / PX] == '1')
			break ;
		mlx_put_pixel(data->img->ray, x, y, 0xFF0000FF);
		mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
	}
}
