/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/16 13:50:16 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Moves player forward by 'steps' based on it's angle position 
  (cos / sin / data->p_a). Size of steps defined in header.
  '- sin' as Y axis decreases upwards. In case there is no wall in the player's
  new position, current location of player gets updated.*/
void	move_up(t_data *data)
{
	double	new_x;
	double	new_y;

	// new_x = data->x_p + cos(data->p_a) * steps;
	// new_y = data->y_p - sin(data->p_a) * steps;
	new_x = data->x_p + data->p_dx * steps;
	new_y = data->y_p - data->p_dy * steps;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		build_map(data);
		mlx_delete_image(data->mlx, data->img->ray);
		create_ray_img(data);
		draw_fov(data);
	}
}

/*Moves player backwards by 'steps' based on it's angle position 
  (cos / sin / data->p_a). Size of steps defined in header.
  '+ sin' as Y axis increases downwards. In case there is no wall in the player's
  new position, current location of player gets updated.*/
void	move_down(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->x_p - data->p_dx * steps;
	new_y = data->y_p + data->p_dy * steps;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		build_map(data);
		mlx_delete_image(data->mlx, data->img->ray);
		create_ray_img(data);
		draw_fov(data);
	}
}

/*Makes player strafe to left by -90 degrees in relation to
  direction facing. Strafe angle calculated by adding 90 degrees
  (PI/2) to current player angle.*/
void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;

	strafe_angle = data->p_a + PI / 2;
	new_x = data->x_p + cos(strafe_angle) * steps;
	new_y = data->y_p - sin(strafe_angle) * steps;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		build_map(data);
		mlx_delete_image(data->mlx, data->img->ray);
		create_ray_img(data);
		draw_fov(data);
	}
}

/*Makes player strafe to right by +90 degrees in relation to
  direction facing. Strafe angle calculated by substracting 90 degrees
  (PI/2) from current player angle.*/
void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;

	strafe_angle = data->p_a - PI / 2;
	new_x = data->x_p + cos(strafe_angle) * steps;
	new_y = data->y_p - sin(strafe_angle) * steps;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		build_map(data);
		mlx_delete_image(data->mlx, data->img->ray);
		create_ray_img(data);
		draw_fov(data);
	}
}
