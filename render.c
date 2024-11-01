/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/01 09:46:50 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	draw_wall_slice(t_data *data, int x, int start_y, int end_y)
{
    uint32_t	colour;
	int			y;

	y = start_y;
	colour = 0;
	if (data->img->hit_dir[x] == 1)
			colour = 0xD3D3D3FF;
		if (data->img->hit_dir[x] == 2)
			colour = 0xC0C0C0FF;
		if (data->img->hit_dir[x] == 3)
			colour = 0xA9A9A9FF;
		if (data->img->hit_dir[x] == 4)
			colour = 0xF5F5F5FF;
	while (y < end_y)
	{
		mlx_put_pixel(data->img->fg, x, y, colour);
		y++;
	}
}

void	render_map(t_data *data)
{
	int			i;
	float		slice_height;
	float		start_y;
	float		end_y;
	float		center_y;

	i = 0;
	slice_height = 0;
	center_y = S_HEI / 2;
	data->dist_plane = (S_WID / 2) / tan(FOV / 2);
	while (i < S_WID)
	{
		slice_height = (BLOCK_SIZE / (data->img->len[i])) * data->dist_plane;
		start_y = center_y - slice_height / 2;
		end_y = center_y + slice_height / 2;
		if (start_y < 0)
			start_y = 0;
		if(end_y >= S_HEI)
			end_y = S_HEI - 1;
		draw_wall_slice(data, i, start_y, end_y);
		i++;
	}
}
