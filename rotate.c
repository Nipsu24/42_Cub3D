/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/30 10:55:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Rotates player counter-clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_left(t_data *data)
{
	data->p_a += RO_SPEED;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	if (data->p_a <= 0)
		data->p_a += 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
	mlx_delete_image(data->mlx, data->img->ray);
	mlx_delete_image(data->mlx, data->img->fg);
	create_ray_img(data);
	create_fg_img(data);
	// draw_fov_3d(data);
	build_map(data);
	// draw_fov(data);
	raycaster(data);
}

/*Rotates player clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_right(t_data *data)
{
	data->p_a -= RO_SPEED;
	if (data->p_a <= 0)
		data->p_a += 2 * PI;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
	mlx_delete_image(data->mlx, data->img->ray);
	mlx_delete_image(data->mlx, data->img->fg);
	create_fg_img(data);
	create_ray_img(data);
	// draw_fov_3d(data);
	build_map(data);
	// draw_fov(data);
	raycaster(data);
}
