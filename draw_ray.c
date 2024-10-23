/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/22 15:54:29 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
static void	draw_single_ray(t_data *data, float angle, int color)
{
	float	x;
	float	y;
	float	mag;

	x = (data->x_p * data->PX); //+ data->PX_mm / 2);
	y = (data->y_p * data->PX); //+ data->PX_mm / 2);
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * ray_speed * data->PX);
		y += (data->ray_dir_y * ray_speed * data->PX);
		if (x < 0 || y < 0 || x >= data->width * data->PX || y >= data->height * data->PX
			|| data->map[(int)y / (int)data->PX][(int)x / (int)data->PX] == '1')
			break ;
		mlx_put_pixel(data->img->ray, x, y, color);
	}
}

void	draw_fov(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	current_angle;
	float	step_angle;

	data->ray_index = 0;
	start_angle = data->p_a - PI / 6;
	end_angle = data->p_a + PI / 6;
	step_angle = (end_angle - start_angle) / mm_rays;
	current_angle = start_angle;
	data->img->colour = 0xFF0000FF;
	while (current_angle <= end_angle)
	{
		draw_single_ray(data, current_angle, data->img->colour);
		current_angle += step_angle;
		data->ray_index++;
		if (data->img->colour == 0xFF0000FF)
			data->img->colour = 0x00FF00FF;
		else if (data->img->colour == 0x00FF00FF)
			data->img->colour = 0x0000FFFF;
		else
			data->img->colour = 0xFF0000FF;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}

/*functions for casting single, individual rays used for '3D' rendering*/

static float	draw_single_ray_3d(t_data *data, float angle)
{
	float	x;
	float	y;
	float	mag;
	float	len;

	x = data->x_p;
	y = data->y_p;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * ray_speed);
		y += (data->ray_dir_y * ray_speed);
		len = sqrt((x - data->x_p) * (x - data->x_p) + (y - data->y_p) * (y - data->y_p));

		if (x < 0 || y < 0 || x >= screen_width || y >= screen_height
			|| data->map[(int)y][(int)x] == '1')
			return (len);
	}
}

static int	find_ray_dir(t_data *data, float angle)
{
	float	x;
	float	y;
	float	mag;
	int		dir;

	x = data->x_p;
	y = data->y_p;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * ray_speed);
		y += (data->ray_dir_y * ray_speed);
		
		if (x < 0 || y < 0 || x >= screen_width || y >= screen_height
			|| data->map[(int)y][(int)x] == '1')
			return (dir) ;
	}
}

static void	updating_fg(t_data *data) //ORGINAL
{
	int		ray_index;
	float	len;
	float	line_height;
	float	start_y;
	float	end_y;
	float	y;
	float	screen_center;
	int		pixel_x;
 
	screen_center = screen_height / 2;
	ray_index = 0;

	while (ray_index < rays)
	{
		len = data->img->len[ray_index];
		if (len == 0)
    		len = 0.01f;
		line_height = (block_height) / len;
		start_y = screen_center - (line_height / 2);
		end_y = screen_center + (line_height / 2);
		y = start_y;
		pixel_x = screen_width - (ray_index * (screen_width / (float)rays));
		while (y <= end_y)
		{
			if (y >= 0 && y < screen_height && data->img->ray_dir[ray_index] == 1)
				mlx_put_pixel(data->img->fg, pixel_x, y, 0x00FFFFFF);
			if (y >= 0 && y < screen_height && data->img->ray_dir[ray_index] == 2)
				mlx_put_pixel(data->img->fg, pixel_x, y, 0xFF00FFFF);
			if (y >= 0 && y < screen_height && data->img->ray_dir[ray_index] == 3)
				mlx_put_pixel(data->img->fg, pixel_x, y, 0xFFFF00FF);
			if (y >= 0 && y < screen_height && data->img->ray_dir[ray_index] == 4)
				mlx_put_pixel(data->img->fg, pixel_x, y, 0x000000FF);
			y += 1;
		}
		ray_index++;
	}
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);	
}


/*functions for casting a series of rays used for '3D' rendering*/

void	draw_fov_3d(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	current_angle;
	float	step_angle;
	int		i;

	
	start_angle = data->p_a - PI / 6;
	end_angle = data->p_a + PI / 6;
	step_angle = (end_angle - start_angle) / rays;
	current_angle = start_angle;
	i = 0;
	while (current_angle <= end_angle && i < rays)
	{
		data->img->len[i] = draw_single_ray_3d(data, current_angle);
		data->img->ray_dir[i] = find_ray_dir(data, current_angle);
		current_angle += step_angle;
		i++;
	}
	updating_fg(data);
	// clean exit
}



