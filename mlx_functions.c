/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/09 15:25:32 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Detects key press and conducts respective actions related to the
  key pressed.*/
static void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_up(data);
		if (keydata.key == MLX_KEY_A)
			move_left(data);
		if (keydata.key == MLX_KEY_S)
			move_down(data);
		if (keydata.key == MLX_KEY_D)
			move_right(data);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_left(data);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_right(data);
		print_arr(data->map);
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
	if (create_ray_img(data))
		return (1);
	if (create_pl_img(data))
		return (1);
	check_init_pl_angle(data);
	build_map(data);
	draw_line(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
