/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/05 16:58:57 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Populates texture variables, texture struct itself is already initialised
  within init_data function.*/
static int	get_textures(t_data *data)
{
	data->txtr->wl = mlx_load_png("./textures/black_wall_mini_map.png");
	if (!data->txtr->wl)
		return (1);
	data->txtr->fl = mlx_load_png("./textures/white_floor_mini_map.png");
	if (!data->txtr->fl)
		return (1);
	data->txtr->pl = mlx_load_png("./textures/player_mini_map.png");
	if (!data->txtr->pl)
		return (1);
	return (0);
}

/*Populates image variables, image struct itself is already initialised
  within init_data function.*/
static int	get_images(t_data *data)
{
	data->img->wl = mlx_texture_to_image(data->mlx, data->txtr->wl);
	if (!data->img->wl)
		return (1);
	data->img->fl = mlx_texture_to_image(data->mlx, data->txtr->fl);
	if (!data->img->fl)
		return (1);
	data->img->pl = mlx_texture_to_image(data->mlx, data->txtr->pl);
	if (!data->img->pl)
		return (1);
	return (0);
}

/*Builds 2d map (floor, wall, player). Deletion and creation of textures and images
  needed in this function, as it is called everytime when a move is conducted (map
  gets again build "from scratch" over and over again).*/
void	build_map(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	del_txtr_only(data);
	del_img_only(data);
	get_textures(data);
	get_images(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			mlx_image_to_window(data->mlx, data->img->fl, x * PX, y * PX);
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img->wl, x * PX, y * PX);
		}
	}
	mlx_image_to_window(data->mlx, data->img->pl, (int)(data->x_p * PX), (int)(data->y_p * PX));
}

/*Detects key press and conducts respective actions related to the
  key pressed.*/
static void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			move_up(data);
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			move_left(data);
		if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			move_down(data);
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			move_right(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
}

int	mlx_functions(t_data *data, t_img *img)
{
	(void)img;
	data->mlx = mlx_init(data->width * PX, data->height * PX, "cub3D", true);
	if (!data->mlx)
		return (1);
	if (get_textures(data))
		return (1);
	if (get_images(data))
		return (1);
	build_map(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
