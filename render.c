/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/08 11:31:36 by mmeier           ###   ########.fr       */
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

/*Helper function of draw_wall_slice, calculates y pixel position
  within the texture, and accounts for cases where those position
  exceed the texture boundaries. Returns colour of pixel to
  draw_wall_slice function.*/
static uint32_t	slice_loop(t_data *data, float start_y, int y, uint32_t colour)
{
	data->txt_y = data->txt_y_st + (y - start_y)
		* (data->texture->height / data->slice_height);
	if (data->txt_x >= data->texture->width)
		data->txt_x = data->texture->width - 1;
	if (data->txt_y >= data->texture->height)
		data->txt_y = data->texture->height - 1;
	colour = get_texture_colour(data->texture,
			(int)data->txt_x, (int)data->txt_y);
	return (colour);
}

/*Maps map coordinates with texture coordinates (txt_x and txt_y)
  in order to retrieve colour of respective pixel from texture with
  help of slice_loop/get_texture_colour function. In case wall slice
  is bigger than screen height, an extra caclulation is conducted for
  txt_y_st to prevent distortion if the player is close to a wall.
  Slice_loop function returns colour of the pixel and internally
  determines y position in the texture. Then the funtion draws the
  pixel with put_pixel function.*/
static void	draw_wall_slice(t_data *data, int x, float start_y, float end_y)
{
	uint32_t	colour;
	int			y;
	float		off_x;

	colour = 0;
	off_x = calc_x_offset(data, x);
	data->txt_x = off_x * data->texture->width;
	if (start_y < 0)
	{
		data->txt_y_st = -start_y
			* (data->texture->height / data->slice_height);
		start_y = 0;
	}
	else
		data->txt_y_st = 0;
	data->txt_y = data->txt_y_st;
	y = start_y;
	while (y < end_y)
	{
		colour = slice_loop(data, start_y, y, colour);
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
