/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/08 14:17:49 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	rotate_left(t_data *data)
{
	data->p_a -= 0.1;
	if (data->p_a < 0)
		data->p_a += 2 * PI;
	data->p_dx = cos (data->p_a) * steps;
	data->p_dy = sin (data->p_a) * steps;
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	create_ray_img(data);
	draw_line(data);
}

void	rotate_right(t_data *data)
{
	// data->p_a = 0;
	// data->p_dx = 0;
	// data->p_dy = 0;
	data->p_a += 0.1;
	if (data->p_a > 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos (data->p_a) * steps;
	data->p_dy = sin (data->p_a) * steps;
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	create_ray_img(data);
	draw_line(data);
}



