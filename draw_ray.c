/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/07 11:32:53 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	create_ray_img(t_data *data)
{
	data->img->ray = mlx_new_image(data->mlx, data->width * PX, data->height * PX);
	if (!data->img->ray)
		return (1);
	return (0);
}

void draw_line(t_data *data)
{
	int	x; 
	int	y; 

	x = (int)data->x_p;
	y = (int)data->y_p;
	while (1)
	{
		if (data->p_dir == 'N')
			y -= ray_speed;
		else if (data->p_dir == 'E')
			x += ray_speed;
		else if (data->p_dir == 'S')
			y += ray_speed;
		else if (data->p_dir == 'W')
			x -= ray_speed;
		if (x < 0 || y < 0 || data->map[y][x] == '1')
			break;
		mlx_put_pixel(data->img->ray, x * PX, y * PX, 0xFF0000FF);
		mlx_image_to_window(data->mlx, data->img->ray, x, y);
	}
}

// void draw_line(t_data *data)
// {
// 	while (1)
// 	{
// 		if (data->p_dir == 'N')
// 			data->y_p -= ray_speed;
// 		else if (data->p_dir == 'E')
// 			data->x_p += ray_speed;
// 		else if (data->p_dir == 'S')
// 			data->y_p += ray_speed;
// 		else if (data->p_dir == 'W')
// 			data->x_p -= ray_speed;
// 		if (data->x_p < 0 || data->y_p < 0 || data->map[(int)data->y_p][(int)data->x_p] == '1')
// 			break;
// 		mlx_put_pixel(data->img->ray, data->x_p * PX, data->y_p * PX, 0xFF0000FF);
// 		// mlx_image_to_window(data->mlx, data->img->ray, data->x_p, data->y_p);
// 	}
// }