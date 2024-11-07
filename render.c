/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/07 11:36:37 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Calculate the offset in the pixel array (4 bytes per pixel
  for RGBA). Then accesses the pixel data at the calculated offset
  and eventually combines the RGBA channels into a single 32-bit
  integer with bitwise operation.*/
static uint32_t	get_texture_colour(mlx_texture_t *texture, int x, int y)
{
	int			pixel_offset;
	uint8_t		*pixel_data;
	uint32_t	colour;

	pixel_offset = 0;
	pixel_data = NULL;
	colour = 0;
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	pixel_offset = (y * texture->width + x) * 4;
	pixel_data = &texture->pixels[pixel_offset];
	colour = (pixel_data[0] << 24) | (pixel_data[1] << 16)
		| (pixel_data[2] << 8) | (pixel_data[3]);
	return (colour);
}

/*Calcluates offset of x coordinate depending on a vertical or
  horizontal wall hit by using modulo calculation with the block
  height (1.0f). At the same time, assigns respective wall texture
  to data->texture variable. x value is the i-index passed from
  render_map function)*/
static float	calc_x_offset(t_data *data, int x)
{
	float	off_x;

	off_x = 0;
	if (data->img->hit_dir[x] == 1 || data->img->hit_dir[x] == 3)
	{
		if (data->img->hit_dir[x] == 1)
			data->texture = data->txtr->no;
		else
			data->texture = data->txtr->so;
		off_x = fmod(data->img->cl_x[x], 1.0f);
	}
	else if (data->img->hit_dir[x] == 2 || data->img->hit_dir[x] == 4)
	{
		if (data->img->hit_dir[x] == 2)
			data->texture = data->txtr->ea;
		else
			data->texture = data->txtr->we;
		off_x = fmod(data->img->cl_y[x], 1.0f);
	}
	return (off_x);
}

/*Maps map coordinates with texture coordinates (txt_x and txt_y)
  in order to retrieve colour of respective pixel from texture with
  help of get_texture_colour function. Then draws the pixel with
  put_pixel function.*/
static void	draw_wall_slice(t_data *data, int x, float start_y, float end_y)
{
	uint32_t	colour;
	int			y;
	float		off_x;
	float		txt_x;
	float		txt_y;
	float		txt_y_start;

	colour = 0;
	off_x = calc_x_offset(data, x);
	txt_x = off_x * data->texture->width;
	if (start_y < 0)
    {
        txt_y_start = -start_y * (data->texture->height / data->slice_height);
        start_y = 0;
    }
    else
        txt_y_start = 0;
    txt_y = txt_y_start;
    y = start_y;
	while (y < end_y)
	{
		txt_y = txt_y_start + (y - start_y) * (data->texture->height / data->slice_height);
		if (txt_x >= data->texture->width)
			txt_x = data->texture->width - 1;
		if (txt_y >= data->texture->height)
			txt_y = data->texture->height - 1;
		colour = get_texture_colour(data->texture, (int)txt_x, (int)txt_y);
		mlx_put_pixel(data->img->fg, x, y, colour);
		y++;
	}
}

/*Uses calculated ray length from raycaster and distance between
  player and plane for determining respective wall slice height.
  Calculates start and end of the wall slice to be drawn, by using
  slice_height and calculated values related to size of the screen.
  i index represents position on x axis (incremented in loop by one pixel).*/
void	render_map(t_data *data)
{
	int			i;
	float		start_y;
	float		end_y;

	i = 0;
	data->dist_plane = (S_WID / 2) / tan(data->fov / 2);
	while (i < S_WID)
	{
		data->slice_height
			= (BLOCK_SIZE / (data->img->len[i])) * data->dist_plane;
		start_y = (S_HEI / 2) - (data->slice_height / 2);
		end_y = (S_HEI / 2) + (data->slice_height / 2);
		if (end_y >= S_HEI)
			end_y = S_HEI - 1;
		draw_wall_slice(data, i, start_y, end_y);
		i++;
	}
}
