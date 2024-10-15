/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/15 16:49:16 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	create_ray_img(t_data *data)
{
	data->img->ray = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->ray)
		return (1);
	return (0);
}

int	create_pl_img(t_data *data)
{
	data->img->pl = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->pl)
		return (1);
	return (0);
}

void	init_hor_inter_values(t_data *data)
{
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->hor_delta_y = 0;
	data->hor_delta_x = 0;
	data->ray_dir_x = cos(data->p_a);
	data->ray_dir_y = -sin(data->p_a);
	data->len_close_hor = 0;
}

void check_closest_hor_inter(t_data *data)
{
	init_hor_inter_values(data);
	if (data->ray_dir_y > 0) // ray moves upwards y-axis (South)
	{
		data->hor_next_y = ceil(data->y_p); //calculates closest int upwards
		data->hor_delta_y = data->hor_next_y - data->y_p;
	}
	if (data->ray_dir_y < 0) // ray moves downwards y-axis (North))
	{
		data->hor_next_y = floor(data->y_p); //calculates closest int downwards
		data->hor_delta_y = data->y_p - data->hor_next_y;
	}
	if (fabs(data->ray_dir_y) < 1e-6) // or check if data->p_a is near 0 or π radians
	{
		data->hor_delta_x = 0;
		if (data->ray_dir_x > 0) // ray moving to right
			data->hor_next_x += 1;
		else if (data->ray_dir_x < 0)
			data->hor_next_x -= 1;
	}
	else
	{
		data->hor_delta_x = 1 / fabs(tan(data->p_a));
		if (data->ray_dir_y > 0)
			data->hor_next_x = data->x_p - data->hor_delta_y / tan(data->p_a);
		if (data->ray_dir_y < 0)
			data->hor_next_x = data->x_p + data->hor_delta_y / tan(data->p_a);	
	}
	data->len_close_hor = sqrt((data->hor_next_x - data->x_p) * (data->hor_next_x - data->x_p)
		+ (data->hor_delta_y - data->y_p) * (data->hor_delta_y - data->y_p));
	draw_ray(data, data->x_p, data->y_p, data->hor_next_x, data->hor_next_y);
}

void	check_horizontal_inter(t_data *data)
{
	double	next_y;
	double	next_x;
	double	delta_y;
	double	delta_x;
	int		up;
	
	delta_x = 0;
	delta_y = 0;
	up = 0;
	next_y = 0;
	next_x = 0;
	data->ray_dir_x = cos(data->p_a);
	data->ray_dir_y = -sin(data->p_a);
	if (data->ray_dir_y > 0) // ray moves upwards y-axis (South)
	{
		next_y = ceil(data->y_p); //calculates closest int upwards
		up = 1;
		delta_y = next_y - data->y_p;
	}
	if (data->ray_dir_y < 0) // ray moves downwards y-axis (North))
	{
		next_y = floor(data->y_p); //calculates closest int downwards
		up = 0;
		delta_y = data->y_p - next_y;
	}
	if (fabs(data->ray_dir_y) < 1e-6) // or check if data->p_a is near 0 or π radians
	{
		delta_x = 0;
		if (data->ray_dir_x > 0) // ray moving to right
			next_x += 1;
		else if (data->ray_dir_x < 0)
			next_x -= 1;
	}
	else
	{
		delta_x = 1 / fabs(tan(data->p_a));
		if (data->ray_dir_y > 0)
			next_x = data->x_p - delta_y / tan(data->p_a);
		if (data->ray_dir_y < 0)
			next_x = data->x_p + delta_y / tan(data->p_a);	
	}
	draw_ray(data, data->x_p, data->y_p, next_x, next_y);
	while (1)
	{
		if (next_y <= 0 || next_x <= 0 || next_y >= data->height
			|| next_x >= ft_strlen(data->map[(int)next_y]) || data->map[(int)next_y][(int)next_x] == '1')
			break ;
		if (data->ray_dir_x > 0) // Ray moving to the right
		{
			if (fabs(data->ray_dir_y) < 1e-6)
				next_x += 1;
			if (up) // Moving upwards (visually downwards)
			{
				next_y += 1;
				next_x += delta_x;
				draw_ray(data, next_x - delta_x, next_y - 1, next_x, next_y);
			}
			else // Moving downwards (visually upwards)
			{
				next_y -= 1;
				next_x += delta_x;
				draw_ray(data, next_x - delta_x, next_y + 1, next_x, next_y);
			}
		}
		else if (data->ray_dir_x < 0) // Ray moving to the left
		{
			if (fabs(data->ray_dir_y) < 1e-6)
				next_x -= 1;
			if (up) // Moving upwards (visually downwards)
			{
				next_y += 1;
				next_x -= delta_x;
				draw_ray(data, next_x + delta_x, next_y - 1, next_x, next_y);
			}
			else // Moving downwards (visually upwards)
			{
				next_y -= 1;
				next_x -= delta_x;
				draw_ray(data, next_x + delta_x, next_y + 1, next_x, next_y);
			}
		}
	}
}

void	check_vertical_inter(t_data *data)
{
	double	next_y;
	double	next_x;
	double	delta_y;
	double	delta_x;
	int		right;
	
	delta_x = 0;
	delta_y = 0;
	right = 0;
	next_y = 0;
	next_x = 0;
	data->ray_dir_x = cos(data->p_a);
	data->ray_dir_y = -sin(data->p_a);
	printf("player y %f\n", data->y_p);
	printf("player x %f\n", data->x_p);
	if (data->ray_dir_x > 0) // ray moves right x-axis
	{
		next_x = ceil(data->x_p); //calculates closest int upwards
		printf("moves right\n");
		printf("next_x %f\n", next_x);
		right = 1;
		delta_x = next_x - data->x_p;
		if(fabs(data->ray_dir_x) < 1e-6)
		{
			if (data->ray_dir_y > 0)
				next_y += 1;
			else if (data->ray_dir_y < 0)
				next_y -= 1;
		}
		else
			next_y = data->y_p - delta_x * tan(data->p_a);
		printf("next_y %f\n", next_y);
	}
	if (data->ray_dir_x < 0) // ray moves left x-axis
	{
		next_x = floor(data->x_p); //calculates closest int downwards
		printf("moves left\n");
		printf("next_x %f\n", next_x);
		right = 0;
		delta_x = data->x_p - next_x;
		if(fabs(data->ray_dir_x) < 1e-6)
		{
			if (data->ray_dir_y > 0)
				next_y += 1;
			else if (data->ray_dir_y < 0)
				next_y -= 1;
		}
		else
			next_y = data->y_p + delta_x * tan(data->p_a);
		printf("next_y %f\n", next_y);
	}
	if(fabs(data->ray_dir_x) < 1e-6)
		delta_y = 0;
	else
		delta_y = fabs(delta_x * tan(data->p_a));
	draw_ray(data, data->x_p, data->y_p, next_x, next_y);
	while (1)
	{
		if (next_y <= 0 || next_x <= 0 || next_y >= data->height
			|| next_x >= ft_strlen(data->map[(int)next_y]) || data->map[(int)next_y][(int)next_x] == '1')
			break ;
		if (data->ray_dir_y > 0) //ray moves upwards y-axis (South)
		{
			if(fabs(data->ray_dir_x) < 1e-6)
				next_y += 1;
			if (right)
			{
				next_x += 1;
				next_y += delta_y;
				draw_ray(data, next_x - 1, next_y - delta_y, next_x, next_y);
			}
			else // Moving left
			{
				next_x -= 1;
				next_y += delta_y;
				draw_ray(data, next_x + 1, next_y - delta_y, next_x, next_y);
			}
		}
		else if (data->ray_dir_y < 0) //ray moves downwards y-axis (North)
		{
			if(fabs(data->ray_dir_x) < 1e-6)
				next_y -= 1;
			if (right)
			{
				next_x += 1;
				next_y -= delta_y;
				draw_ray(data, next_x - 1, next_y + delta_y, next_x, next_y);
			}
			else // Moving left
			{
				next_x -= 1;
				next_y -= delta_y;
				draw_ray(data, next_x + 1, next_y + delta_y, next_x, next_y);
			}
		}
		// printf("next y %f\n", next_y);
		// printf("next x %f\n", next_x);
	}
}

static int f_abs(int n)
{ 
	return ((n > 0) ? n : (n * (-1)));
}
 
void	draw_ray(t_data *data, float x, float y, float x_tar, float y_tar)
{
	float	dx;
	float	dy;
	int		steps_n;
	float	x_inc;
	float	y_inc;
	int		i;

	x = x * 64 + PXP / 2;
	y = y * 64 + PXP / 2;
	x_tar = x_tar * 64 + PXP / 2;
	y_tar = y_tar * 64 + PXP / 2;
	i = 0;
	dx = x_tar - x;
	dy = y_tar - y;
	steps_n = f_abs(dx) > f_abs(dy) ? f_abs(dx) : f_abs(dy);
	x_inc = dx / (float)steps_n;
	y_inc = dy / (float)steps_n;

	while (i <= steps_n)
	{
		mlx_put_pixel(data->img->ray, x, y,  0xFF0000FF);
		x += x_inc;
		y += y_inc;
		i++;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}


/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
void	draw_line(t_data *data)
{
	// int		x;
	// int		y;
	// float	magnitude;

	check_horizontal_inter(data);
	// check_vertical_inter(data);
	// x = (int)(data->x_p * PX) + PXP / 2;
	// y = (int)(data->y_p * PX) + PXP / 2;
	// data->ray_dir_x = cos(data->p_a);
	// data->ray_dir_y = -sin(data->p_a);
	// magnitude = sqrt(data->ray_dir_x * data->ray_dir_x
	// 		+ data->ray_dir_y * data->ray_dir_y);
	// data->ray_dir_x /= magnitude;
	// data->ray_dir_y /= magnitude;
	// while (1)
	// {
	// 	x += (int)(data->ray_dir_x * ray_speed * PX);
	// 	y += (int)(data->ray_dir_y * ray_speed * PX);
	// 	if (x < 0 || y < 0 || x >= data->width * PX || y >= data->height * PX
	// 		|| data->map[y / PX][x / PX] == '1')
	// 		break ;
	// 	mlx_put_pixel(data->img->ray, x, y, 0xFF0000FF);
	// 	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
	// }
}
