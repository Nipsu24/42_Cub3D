/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 11:35:52 by mmeier           ###   ########.fr       */
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

static void	init_raycaster(t_data *data)
{
	data->start_angle = data->p_a - FOV / 2;
	data->end_angle = data->p_a + FOV / 2;
	data->step_angle = FOV / S_WID;
	data->ray_or = data->end_angle;
}

static void set_up_intersec_check(t_data *data)
{
	normalize_angle(&data->ray_or, &data->start_angle);
	init_draw_ray(data);
	check_closest_hor_inter(data);
	check_closest_ver_inter(data);
	calc_delta_ver(data);
	calc_delta_hor(data);
}

void	raycaster(t_data *data)
{
	int	i;

	i = 0;
	init_raycaster(data);
	while (data->ray_or >= data->start_angle)
	{
		set_up_intersec_check(data);
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
		draw_ray(data, i);
		data->ray_or -= data->step_angle;
		i++;
	}
	render_map(data);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
