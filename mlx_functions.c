/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/05 09:34:57 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

// static void mouse_catcher(float xpos, float ypos, void* param)
// {
//     t_data *data = (t_data *)param;

// 	(void) ypos;
//     // Adjust the player's angle (horizontal rotation)
//     data->p_a += xpos * 0.001;//MOUSE_SENSITIVITY

   
//     if (data->p_a < 0)
//         data->p_a += 2 * M_PI;
// 	if (data->p_a > 2 * M_PI)
//         data->p_a -= 2 * M_PI;

//     // Optionally redraw the view or FOV
// 	build_map(data);
// 	mlx_delete_image(data->mlx, data->img->ray);
// 	create_ray_img(data);
//     draw_fov(data);  // Call your raycasting function here
// }

/*Detects key press and conducts respective actions related to the
  key pressed.*/
static void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx, data->img->ray);
	mlx_delete_image(data->mlx, data->img->fg);
	create_fg_img(data);
	create_ray_img(data);
	raycaster(data);
	build_map(data);
	// if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	// {
		// if (keydata.key == MLX_KEY_W)
		// 	move_up(data);
		// if (keydata.key == MLX_KEY_A)
		// 	move_left(data);
		// if (keydata.key == MLX_KEY_S)
		// 	move_down(data);
		// if (keydata.key == MLX_KEY_D)
		// 	move_right(data);
		// if (keydata.key == MLX_KEY_LEFT)
		// 	rotate_left(data);
		// if (keydata.key == MLX_KEY_RIGHT)
		// 	rotate_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data);
	// }
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
}

/*Converts RGB colour values into a single hex value, with alpha value
  (opaque value) set to 255 (0xFF). Performs bitshifting operation:
  R shifted to highest octet, G to second highest, b to third octet.*/
  
static uint32_t convert_rgb_to_hex(long *rgb)
{
    uint32_t	hex_value;
	
    hex_value = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;             
    return (hex_value);
}

/*Draws background of 3d world, splits screen horizontally into two colours
  determined by ceiling and floor values retrieved from map data file. */
static void	fill_main_screen(t_data *data)
{
	float y;
	float x;

	y = -1;
	x = -1;
	while (++y < S_HEI / 2)
	{
		x = -1;
		while (++x < S_WID)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->ceiling));
	}
	y--;
	while (++y < S_HEI)
	{
		x = -1;
		while (++x < S_WID)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->floor));
	}
	mlx_image_to_window(data->mlx, data->img->bg, 0, 0);
}

/*Calculates dynamic tile size in pixels. MM_SIZE is arbitrary downscale 
  factor of the minimap in relation to the main screen. If / else statement
  in order to avoid scale distortion of the equally squared tiles.*/
void calc_mini_map_scaling(t_data *data)
{
    int PX_x = 0;
    int PX_y = 0;

    PX_x = S_WID / data->width / MM_SIZE;
    PX_y = S_HEI / data->height / MM_SIZE;
    if (PX_x < PX_y)
		data->PX = PX_x;
	else
		data->PX = PX_y;
}

int	mlx_functions(t_data *data)
{
	if (create_bg_img(data))
		return (1);
	fill_main_screen(data);
	calc_mini_map_scaling(data);
	if (get_textures(data))
		return (1);
	printf("TEST\n");
	if (get_images(data))
		return (1);
	if (create_ray_img(data))
		return (1);
	if (create_pl_img(data))
		return (1);
	if (create_fg_img(data))
		return (1);
	check_init_pl_angle(data);
	raycaster(data);
	build_map(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	// mlx_cursor_hook(data->mlx, &mouse_catcher, data);
	mlx_loop(data->mlx);
	return (0);
}
