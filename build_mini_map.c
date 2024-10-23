/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:40:41 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/23 15:01:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Populates texture variables, texture struct itself is already initialised
  within init_data function.*/
int	get_textures(t_data *data)
{
	data->txtr->wl = mlx_load_png("./textures/black_wall_mini_map.png");
	if (!data->txtr->wl)
		return (1);
	data->txtr->fl = mlx_load_png("./textures/white_floor_mini_map.png");
	if (!data->txtr->fl)
		return (1);
	return (0);
}

/*Populates image variables, image struct itself is already initialised
  within init_data function.*/
int	get_images(t_data *data)
{
	data->img->wl = mlx_texture_to_image(data->mlx, data->txtr->wl);
	if (!data->img->wl)
		return (1);
	data->img->fl = mlx_texture_to_image(data->mlx, data->txtr->fl);
	if (!data->img->fl)
		return (1);
	mlx_resize_image(data->img->wl, data->PX, data->PX);
	mlx_resize_image(data->img->fl, data->PX, data->PX);
	return (0);
}

/*Initialises variables of the player struct used in draw_player function.*/
static void	init_pl(t_pl *pl)
{
	pl->x_strt = 0;
	pl->y_strt = 0;
	pl->pix_x = -1;
	pl->pix_y = -1;
	pl->fnl_x = 0;
	pl->fnl_y = 0;
}

/*-strt: calculates starting position of player
  -fnl: translates pixel back to original position, uses round
   function for better accuracy*/
void	draw_player(t_data *data, float width, float height)
{
    t_pl	pl;

	init_pl(&pl);
	pl.x_strt = (data->x_p * data->PX);
	pl.y_strt = (data->y_p * data->PX);
	while (++pl.pix_y <= height)
	{
		pl.pix_x = -1;
		while (++pl.pix_x <= width)
		{
			pl.fnl_x = round(pl.x_strt + pl.pix_x);
			pl.fnl_y = round(pl.y_strt + pl.pix_y);

			if (pl.fnl_x >= 0 && pl.fnl_x < data->width * data->PX
				&& pl.fnl_y >= 0 && pl.fnl_y < data->height * data->PX)
			{
				mlx_put_pixel(data->img->pl, pl.fnl_x, pl.fnl_y, 0x00FF00FF);
				mlx_image_to_window(data->mlx, data->img->pl, 0, 0);
			}
		}
	}
}

/*Builds 2d map (floor, wall, player). Deletion and creation of textures
  and images needed in this function, as it is called everytime when a
  move is conducted (map gets again build "from scratch" over and over
  again).*/
void	build_map(t_data *data)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	del_txtr_only(data);
	del_img_only(data);
	get_textures(data);
	get_images(data);
	create_pl_img(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			mlx_image_to_window(data->mlx, data->img->fl, x * data->PX, y * data->PX);
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img->wl, x * data->PX, y * data->PX);
		}
	}
	data->pl_size = data->PX / mm_size / 2;
	draw_player(data, data->pl_size, data->pl_size);
}
