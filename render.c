/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/04 11:34:47 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Uses hit_dir information (from calc_ray_len function) in order to 
  determine the colour of the wall to be drawn. Then loops through y
  values from top to bottom and draws wall slice with put_pixel function
  (x value is the i-index passed from render_map function).*/
static void	draw_wall_slice(t_data *data, int x, int start_y, int end_y)
{
    uint32_t	colour;
	int			y;

	y = start_y;
	colour = 0;
	if (data->img->hit_dir[x] == 1)
			colour = 0xA9A9A9FF;
		if (data->img->hit_dir[x] == 2)
			colour = 0xC0C0C0FF;
		if (data->img->hit_dir[x] == 3)
			colour = 0xF5F5F5FF;
		if (data->img->hit_dir[x] == 4)
			colour = 0xD3D3D3FF;
	while (y < end_y)
	{
		mlx_put_pixel(data->img->fg, x, y, colour);
		y++;
	}
}

/*Uses calculated ray length from raycaster and distance between player and plane
  for determining respective wall slice height. Calculates start and end of the
  wall slice to be drawn, by using slice_height and calculated values related to size
  of the screen. i index represents position on x axis (incremented in loop by one pixel).*/
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
