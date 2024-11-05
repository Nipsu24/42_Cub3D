/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/05 10:47:42 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Uses hit_dir information (from calc_ray_len function) in order to 
  determine the colour of the wall to be drawn. Then loops through y
  values from top to bottom and draws wall slice with put_pixel function
  (x value is the i-index passed from render_map function).*/
// static void	draw_wall_slice(t_data *data, int x, int start_y, int end_y, float slice_height)
// {
//     uint32_t	colour;
// 	int			y;
// 	float		off_x;
// 	float		txt_x;
// 	float		txt_y;

// 	y = start_y;
// 	colour = 0;
// 	if (data->img->hit_dir[x] == 1)
// 	{
// 		// colour = 0xA9A9A9FF;
// 		off_x = data->cl_x % 1;//BLOCK_SIZE;
// 	}
// 	if (data->img->hit_dir[x] == 2)
// 	{
// 		// colour = 0xC0C0C0FF;
// 		off_x = data->cl_y % BLOCK_SIZE;
// 	}
// 	if (data->img->hit_dir[x] == 3)
// 	{
// 		// colour = 0xF5F5F5FF;
// 		off_x = data->cl_x % BLOCK_SIZE;
// 	}
// 	if (data->img->hit_dir[x] == 4)
// 	{
// 		// colour = 0xD3D3D3FF;
// 		off_x = data->cl_y % BLOCK_SIZE;
// 	}
// 	txt_x = off_x * BITMAP_PX;
// 	while (y < end_y)
// 	{
// 		txt_y = (y / slice_height) * BITMAP_PX;
// 		mlx_put_pixel(data->img->fg, x, y, colour);
// 		y++;
// 	}
// }

// Function to get the color of a pixel at (x, y) in the texture
static uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y) 
{
	int			pixel_offset;
	uint8_t		*pixel_data;
	uint32_t	color;

	pixel_offset = 0;
	pixel_data = NULL;
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	// Calculate the offset in the pixel array (4 bytes per pixel for RGBA)
	pixel_offset = (y * texture->width + x) * 4;

	// Access the pixel data at the calculated offset
	pixel_data = &texture->pixels[pixel_offset];

	// Combine the RGBA channels into a single 32-bit integer (assuming RGBA format)
	color = (pixel_data[0] << 24) | // Red
		(pixel_data[1] << 16) | // Green
		(pixel_data[2] << 8)  | // Blue
		(pixel_data[3]);       // Alpha
	return (color);
}

static void draw_wall_slice(t_data *data, int x, int start_y, int end_y, float slice_height)
{
	uint32_t    	colour;
	int         	y;
	float       	off_x = 0;
	float       	txt_x = 0;
	float       	txt_y = 0;
	mlx_texture_t 	*texture;

	texture = NULL;
	y = start_y;
	y = 0;
	if (data->img->hit_dir[x] == 1 || data->img->hit_dir[x] == 3) 
	{
		if (data->img->hit_dir[x] == 1)
			texture = data->txtr->no;
		else
			texture = data->txtr->so;
		off_x = fmod(data->cl_x, 1.0f);
	}
	else if (data->img->hit_dir[x] == 2 || data->img->hit_dir[x] == 4) 
	{
		if (data->img->hit_dir[x] == 2)
			texture = data->txtr->ea;
		else
			texture = data->txtr->we;
		off_x = fmod(data->cl_y, 1.0f);
	}
	// Map to texture's x-coordinate (horizontal position within the texture)
	txt_x = off_x * texture->width;
	while (y < end_y) 
	{
		// Map this to the texture's y-coordinate (vertical position within the texture)
		// txt_y = (y / slice_height) * texture->height;
		txt_y = ((float)(y - start_y) / slice_height) * texture->height;
		// Ensure texture coordinates are within bounds
		if (txt_x >= texture->width) 
			txt_x = texture->width - 1;
		if (txt_y >= texture->height) 
			txt_y = texture->height - 1;

		// Get color from texture bitmap
		colour = get_texture_color(texture, (int)txt_x, (int)txt_y);
		// Draw pixel on screen
		mlx_put_pixel(data->img->fg, x, y, colour);
		// mlx_get_pixel(data->img->fg, x, y);
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
		draw_wall_slice(data, i, start_y, end_y, slice_height);
		i++;
	}
}







// // Function to get the color of a pixel at (x, y) in the texture
// static uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y) 
// {
// 	int			pixel_offset;
// 	uint8_t		*pixel_data;
// 	uint32_t	color;

// 	pixel_offset = 0;
// 	pixel_data = NULL;
// 	if (x < 0 || x >= BITMAP_PX || y < 0 || y >= BITMAP_PX)
// 		return (0);
// 	// Calculate the offset in the pixel array (4 bytes per pixel for RGBA)
// 	pixel_offset = (y * BITMAP_PX + x) * 4;

// 	// Access the pixel data at the calculated offset
// 	pixel_data = &texture->pixels[pixel_offset];

// 	// Combine the RGBA channels into a single 32-bit integer (assuming RGBA format)
// 	color = (pixel_data[0] << 24) | // Red
// 		(pixel_data[1] << 16) | // Green
// 		(pixel_data[2] << 8)  | // Blue
// 		(pixel_data[3]);       // Alpha
// 	return (color);
// }

// static void draw_wall_slice(t_data *data, int x, int start_y, int end_y, float slice_height)
// {
// 	uint32_t    colour;
// 	int         y;
// 	float       off_x = 0;
// 	float       txt_x = 0;
// 	float       txt_y = 0;
// 	mlx_texture_t *texture;

// 	y = start_y;
// 	if (data->img->hit_dir[x] == 1 || data->img->hit_dir[x] == 3) 
// 	{
// 		if (data->img->hit_dir[x] == 1)
// 			texture = data->txtr->no;
// 		else
// 			texture = data->txtr->so;
// 		off_x = fmod(data->cl_x, 1.0f);
// 	}
// 	else if (data->img->hit_dir[x] == 2 || data->img->hit_dir[x] == 4) 
// 	{
// 		if (data->img->hit_dir[x] == 2)
// 			texture = data->txtr->ea;
// 		else
// 			texture = data->txtr->we;
// 		off_x = fmod(data->cl_y, 1.0f);
// 	}
// 	// Map to texture's x-coordinate (horizontal position within the texture)
// 	printf("offset x: %f\n", off_x);
// 	txt_x = off_x * BITMAP_PX;
// 	while (y < end_y) 
// 	{
// 		// Map this to the texture's y-coordinate (vertical position within the texture)
// 		txt_y = (y / slice_height) * BITMAP_PX;

// 		// Ensure texture coordinates are within bounds
// 		if (txt_x >= BITMAP_PX) 
// 			txt_x = BITMAP_PX - 1;
// 		if (txt_y >= BITMAP_PX) 
// 			txt_y = BITMAP_PX - 1;

// 		// Get color from texture bitmap
// 		colour = get_texture_color(texture, (int)txt_x, (int)txt_y);
// 		// Draw pixel on screen
// 		mlx_put_pixel(data->img->fg, x, y, colour);
// 		y++;
// 	}
// }


// /*Uses calculated ray length from raycaster and distance between player and plane
//   for determining respective wall slice height. Calculates start and end of the
//   wall slice to be drawn, by using slice_height and calculated values related to size
//   of the screen. i index represents position on x axis (incremented in loop by one pixel).*/
// void	render_map(t_data *data)
// {
// 	int			i;
// 	float		slice_height;
// 	float		start_y;
// 	float		end_y;
// 	float		center_y;
	
// 	i = 0;
// 	slice_height = 0;
// 	center_y = S_HEI / 2;
// 	data->dist_plane = (S_WID / 2) / tan(FOV / 2);
// 	while (i < S_WID)
// 	{
// 		slice_height = (BLOCK_SIZE / (data->img->len[i])) * data->dist_plane;
// 		start_y = center_y - slice_height / 2;
// 		end_y = center_y + slice_height / 2;
// 		if (start_y < 0)
// 			start_y = 0;
// 		if(end_y >= S_HEI)
// 			end_y = S_HEI - 1;
// 		draw_wall_slice(data, i, start_y, end_y, slice_height);
// 		i++;
// 	}
// }
