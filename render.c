/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/31 13:23:11 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	render_map(t_data *data)
{
	int		i;
	float	slice_height;
	float	start_y;
	float	end_y;
	float	center_y;

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
		draw_wall_slice(data, i, start_y, i, end_y);
		i++;
	}
}
