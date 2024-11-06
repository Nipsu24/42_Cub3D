/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:40:41 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/06 11:13:31 by mmeier           ###   ########.fr       */
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
	data->txtr->no = mlx_load_png(data->img->no);
	if (!data->txtr->no)
		return (1);
	data->txtr->ea = mlx_load_png(data->img->ea);
	if (!data->txtr->ea)
		return (1);
	data->txtr->so = mlx_load_png(data->img->so);
	if (!data->txtr->so)
		return (1);
	data->txtr->we = mlx_load_png(data->img->we);
	if (!data->txtr->we)
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
	del_img_only(data);
	get_images(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			mlx_image_to_window(data->mlx, data->img->fl,
				x * data->PX, y * data->PX);
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img->wl,
					x * data->PX, y * data->PX);
		}
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
