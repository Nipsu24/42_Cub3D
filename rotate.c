/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/18 13:55:58 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Rotates player counter-clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_left(t_data *data)
{
	data->p_a += ro_speed;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	mlx_delete_image(data->mlx, data->img->fg);
	create_ray_img(data);
	create_fg_img(data);
	draw_fov_3d(data);
	draw_fov(data);
}

/*Rotates player clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_right(t_data *data)
{
	data->p_a -= ro_speed;
	if (data->p_a < 0)
		data->p_a += 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	mlx_delete_image(data->mlx, data->img->fg);
	create_ray_img(data);
	create_fg_img(data);
	draw_fov_3d(data);
	draw_fov(data);
}
