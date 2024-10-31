/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/31 15:24:05 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	init_draw_ray(t_data *data)
{
	data->ver_next_y = 0;
	data->ver_next_x = 0;
	data->ver_dis = 0;
	data->ver_hit = 0;
	data->ver_x_step = 0;
	data->ver_y_step = 0;
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->hor_dis = 0;
	data->hor_hit = 0;
	data->hor_y_step = 0;
	data->hor_x_step = 0;
	data->cl_y = 0;
	data->cl_x = 0;
	data->cl_dis = 0;
	data->ray_len = 0;
}

static void	step_forward(t_data *data)
{
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
}

void	raycaster(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	step_angle;
	int		i;

	i = 0;
	start_angle = data->p_a - FOV / 2;
	end_angle = data->p_a + FOV / 2;
	step_angle = FOV / S_WID;
	data->ray_or = start_angle;
	while (data->ray_or <= end_angle)
	{
		normalize_angle(&data->ray_or, &end_angle);
		init_draw_ray(data);
		check_closest_hor_inter(data);
		check_closest_ver_inter(data);
		calc_delta_ver(data);
		calc_delta_hor(data);
		while (1)
		{
			ft_hit_wall(data);
			step_forward(data);
			if (data->ver_hit && data->hor_hit)
				break;
		}
		data->img->len[i] = calc_ray_len(data);
		data->img->len[i] = data->img->len[i] * cos(data->ray_or - data->p_a); // corrects fishbowl effect
		data->img->hit_dir[i] = data->hit_dir;
		if (data->cl_y >= 0 && data->cl_y < data->height && data->cl_x >= 0 && data->cl_x < data->width && i % RAYS_MODULO == 0)
			draw_line_mm(data, data->x_p * data->PX, data->y_p * data->PX, data->cl_x * data->PX, data->cl_y * data->PX);
		data->ray_or += step_angle;
		i++;
	}
	render_map(data);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
