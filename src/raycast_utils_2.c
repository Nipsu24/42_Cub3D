/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:39:00 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/11 12:47:04 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Calculates distance between 2 coordinates of the same axis.
  Values used in order to determine step_size for minimap ray
  in calc_step_size function.*/
static int	calc_tar_dist(float coord, float tar_coord)
{
	float	dist;

	dist = tar_coord - coord;
	return (dist);
}

/*Calculates and returns step size of the ray drawn in minimap. Steps
  later used in init_draw_ray function in order to determine increment
  for the x and y coordinates of the ray line.*/
static int	calc_step_size(float dx, float dy)
{
	int	steps;

	steps = 0;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	return (steps);
}

/*Initialises variables and calculates relevant values for drawing
  ray in minimap. ray_x and ray_y set equal to player position in
  order to avoid using the player position coordinates directly and 
  altering the player position later in the while loop of the
  draw_ray function. Multiplicatio by PX to draw pixel at correct
  position of the map.*/
static void	init_draw_ray(t_data *data, t_ray *ray)
{
	ray->dx = 0;
	ray->dy = 0;
	ray->steps = 0;
	ray->x_inc = 0;
	ray->y_inc = 0;
	ray->j = 0;
	ray->x = 0;
	ray->y = 0;
	ray->dx = calc_tar_dist(data->x_p * data->px, data->cl_x * data->px);
	ray->dy = calc_tar_dist(data->y_p * data->px, data->cl_y * data->px);
	ray->steps = calc_step_size(ray->dx, ray->dy);
	ray->x_inc = ray->dx / (float)ray->steps;
	ray->y_inc = ray->dy / (float)ray->steps;
	ray->x = data->x_p;
	ray->y = data->y_p;
	ray->x *= data->px;
	ray->y *= data->px;
}

/*Draws ray in minimap. Index i from raycaster function used in order
  to determine with help of modulo calculation which ray is drawn (to
  avoid that each ray used for wall projection is drawn in map). Start
  and end values for x and y are used for calculating optimal stepsize
  of putting pixel on the ray line.*/
void	draw_ray(t_data *data, int i)
{
	init_draw_ray(data, data->ray);
	if (data->cl_y >= 0 && data->cl_y < data->height
		&& data->cl_x >= 0 && data->cl_x < data->width
		&& i % RAYS_MODULO == 0)
	{	
		while (data->ray->j <= data->ray->steps)
		{
			mlx_put_pixel(data->img->ray,
				(int)(data->ray->x), (int)(data->ray->y), 0xFF0000FF);
			data->ray->x += data->ray->x_inc;
			data->ray->y += data->ray->y_inc;
			data->ray->j++;
		}
	}
}

int	arr_check(long int *arr)
{
	if (arr[0] < 0 || arr[0] > 255)
		return (1);
	if (arr[1] < 0 || arr[1] > 255)
		return (1);
	if (arr[2] < 0 || arr[2] > 255)
		return (1);
	return (0);

}
