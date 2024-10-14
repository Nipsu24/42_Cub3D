/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/14 16:34:29 by mmeier           ###   ########.fr       */
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
	printf("player y %f\n", data->y_p);
	printf("player x %f\n", data->x_p);
	if (data->ray_dir_y > 0) // ray moves upwards y-axis (South)
	{
		next_y = ceil(data->y_p); //calculates closest int upwards
		printf("moves upwards\n");
		printf("next_y %f\n", next_y);
		up = 1;
		delta_y = next_y - data->y_p;
		next_x = data->x_p - delta_y / tan(data->p_a);
		printf("next_x %f\n", next_x);
	}
	if (data->ray_dir_y < 0) // ray moves downwards y-axis (North))
	{
		next_y = floor(data->y_p); //calculates closest int downwards
		printf("moves downwards\n");
		printf("next_y %f\n", next_y);
		up = 0;
		delta_y = data->y_p - next_y;
		next_x = data->x_p + delta_y / tan(data->p_a);
		printf("next_x %f\n", next_x);
	}
	delta_x = 1 / fabs(tan(data->p_a));
	while (1)
	{
		if (data->ray_dir_x > 0) // Ray moving to the right
		{
			if (up) // Moving upwards (visually downwards)
			{
				next_y += 1;
				next_x += delta_x;
			}
			else // Moving downwards (visually upwards)
			{
				next_y -= 1;
				next_x += delta_x;
			}
		}
		else if (data->ray_dir_x < 0) // Ray moving to the left
		{
			if (up) // Moving upwards (visually downwards)
			{
				next_y += 1;
				next_x -= delta_x;
			}
			else // Moving downwards (visually upwards)
			{
				next_y -= 1;
				next_x -= delta_x;
			}
		}
		printf("next y %f\n", next_y);
		printf("next x %f\n", next_x);
		if (next_y <= 0 || next_x <= 0 || next_y >= data->height
			|| next_x >= ft_strlen(data->map[(int)next_y]) || data->map[(int)next_y][(int)next_x] == '1')
			break ;
	}
}

static void	check_vertical_inter(t_data *data)
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
		next_y = data->y_p + delta_x * tan(data->p_a);
		printf("next_y %f\n", next_y);
	}
	delta_y = fabs(delta_x * tan(data->p_a));
	while (1)
	{
		if (data->ray_dir_y > 0) //ray moves upwards y-axis (South)
		{
			if (right)
			{
				next_x += 1;
				next_y += delta_y;
			}
			else // Moving left
			{
				next_x -= 1;
				next_y += delta_y;
			}
		}
		else if (data->ray_dir_y < 0) //ray moves downwards y-axis (North)
		{
			if (right)
			{
				next_x += 1;
				next_y -= delta_y;
			}
			else // Moving left
			{
				next_x -= 1;
				next_y -= delta_y;
			}
		}
		printf("next y %f\n", next_y);
		printf("next x %f\n", next_x);
		if (next_y <= 0 || next_x <= 0 || next_y >= data->height
			|| next_x >= ft_strlen(data->map[(int)next_y]) || data->map[(int)next_y][(int)next_x] == '1')
			break ;
	}
}



/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
void	draw_line(t_data *data)
{
	int		x;
	int		y;
	float	magnitude;

	// check_horizontal_inter(data);
	check_vertical_inter(data);
	x = (int)(data->x_p * PX) + PXP / 2;
	y = (int)(data->y_p * PX) + PXP / 2;
	data->ray_dir_x = cos(data->p_a);
	data->ray_dir_y = -sin(data->p_a);
	magnitude = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= magnitude;
	data->ray_dir_y /= magnitude;
	while (1)
	{
		x += (int)(data->ray_dir_x * ray_speed * PX);
		y += (int)(data->ray_dir_y * ray_speed * PX);
		if (x < 0 || y < 0 || x >= data->width * PX || y >= data->height * PX
			|| data->map[y / PX][x / PX] == '1')
			break ;
		mlx_put_pixel(data->img->ray, x, y, 0xFF0000FF);
		mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
	}
}



// void check_horizontal_inter(t_data *data)
// {
	
// }

// void	draw_line(t_data *data)
// {
// 	int		r = 0;
// 	int		mx;
// 	int 	my;
// 	int 	mp;
// 	int 	dof;
// 	float	ra;
// 	float	ry;
// 	float	rx;
// 	float	yo;
// 	float	xo;

// 	ra = data->p_a;
// 	while (r < 1)
// 	{
// 		dof=0;
// 		float aTAN = -1/tan(ra);
// 		if (ra > M_PI)
// 		{
// 			ry = (((int)data->y_p>6)<<6)-0.0001;
// 			rx = (data->p_dy - ry) *aTAN + data->x_p;
// 			yo = -64;
// 			xo = -yo * aTAN;
// 		}
// 		if (ra < M_PI)
// 		{
// 			ry = (((int)data->y_p>6)<<6) + 64;
// 			rx = (data->p_dy - ry) *aTAN + data->x_p;
// 			yo = 64;
// 			xo = -yo * aTAN;
// 		}
// 		// if (ra == 0 || ra == PI)
// 		// {
// 		// 	rx = data->x_p;
// 		// 	ry = data->y_p;
// 		// 	dof = 8;
// 		// }
// 		if (fabs(ra) < EPSILON || fabs(ra - PI) < EPSILON)
// 		{
// 			rx = data->x_p;
// 			ry = data->y_p;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int) (rx) >> 6;
// 			my = (int) (ry) >> 6;
// 			mp = my * data->width + mx;
// 			if (mp < data->width * data->height && data->map[my][mx] == '1')
// 				dof = 8;
// 			else
// 			{
// 				mlx_put_pixel(data->img->ray, (int)(rx), (int)(ry), 0xFF0000FF);
// 				rx +=xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 		r++;
// 	}
// 	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
// }
