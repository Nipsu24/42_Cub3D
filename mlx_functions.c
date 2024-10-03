/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/03 17:35:16 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static void	build_floor(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	{
		while (data->map[y])
		{
			x = 0;
			while (data->map[y][x])
			{
				mlx_image_to_window(data->mlx, data->img->fl, x * PX, y * PX);
				if (data->map[y][x] == '1')
					mlx_image_to_window(data->mlx, data->img->wl, x * PX, y * PX);
				x++;
			}
			y++;
		}
	}
}

static void	build_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	{
		build_floor(data);
		while (data->map[y])
		{
			x = 0;
			while (data->map[y][x])
			{
				if (data->map[y][x] == 'N' || data->map[y][x] == 'E'
					|| data->map[y][x] == 'S' || data->map[y][x] == 'W')
					mlx_image_to_window(data->mlx, data->img->pl, x * PX, y * PX);
				x++;
			}
			y++;
		}
	}
}

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

// static void center_player(t_data *data) 
// {
// 	data->x_p = (data->x_p * PX) + PX / 2;
// 	data->y_p = (data->y_p * PX) + PX / 2;
// }

int	mlx_functions(t_data *data, t_img *img)
{
	(void)img;
	data->mlx = mlx_init(data->width * PX, data->height * PX, "cub3D", false);
	if (!data->mlx)
		return (1);
	if (get_textures(data))
		return (1);
	if (get_images(data))
		return (1);
	build_map(data);
	// center_player(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
