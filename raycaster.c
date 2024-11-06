/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:28:22 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/06 15:22:09 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Initialises variables for further raycasting. Function
  used in 'set_up_intersec_check' function.*/
static void	init_draw_ray(t_data *data)
{
	data->ver_next_y = 0;
	data->ver_next_x = 0;
	data->ver_dis = 0;
	data->ver_hit = 0;
	data->ver_x_step = 0;
	data->ver_y_step = 0;
	data->hor_next_y = 0;
	data->hor_next_x = 0;
	data->hor_dis = 0;
	data->hor_hit = 0;
	data->hor_y_step = 0;
	data->hor_x_step = 0;
	data->cl_y = 0;
	data->cl_x = 0;
	data->cl_dis = 0;
	data->ray_len = 0;
}

/*Increments coordinate values of x and y in case
  there are not any intersections at walls
  detected yet. Step size determiined by calc_delta
  functions (see intersects.c)*/
static void	step_forward(t_data *data)
{
	if (!data->hor_hit)
	{
		data->hor_next_x += data->hor_x_step;
		data->hor_next_y += data->hor_y_step;
	}
	if (!data->ver_hit)
	{
		data->ver_next_x += data->ver_x_step;
		data->ver_next_y += data->ver_y_step;
	}
}

/*Calculates relevant values for creating arc
  of rays. Field of view (fov) set to 60 degrees*/
static void	init_raycaster(t_data *data)
{
	data->fov = PI / 3;
	data->start_angle = data->p_a - data->fov / 2;
	data->end_angle = data->p_a + data->fov / 2;
	data->step_angle = data->fov / S_WID;
	data->ray_or = data->end_angle;
}

/*Determines relevant values for the intersections' check
  which is needed later in while loop for incrementing the
  ray lengths until a wall is hit.*/
static void	set_up_intersec_check(t_data *data)
{
	normalize_angle(&data->ray_or, &data->start_angle);
	init_draw_ray(data);
	check_closest_hor_inter(data);
	check_closest_ver_inter(data);
	calc_delta_ver(data);
	calc_delta_hor(data);
}

/*Uses vertical and horizontal intersection check in order to
  determine if a ray hits a wall. When both, vertical and horizontal
  intersection checks detect wall hits, breaks out of inner while loop
  and compares the both ray distances in calc_ray_len function. Then
  stores shorter distance in array of floats for later utilization in
  render map function. Cos multiplication for correction of fish-bowl-effect.
  Also, array of floats for hit direction gets populated. Rays are drawn 
  in minimap with draw_ray function. Render map function ultimately draws 
  wall slices based on ray length on the screen.*/
void	raycaster(t_data *data)
{
	int	i;

	i = 0;
	init_raycaster(data);
	while (data->ray_or >= data->start_angle)
	{
		set_up_intersec_check(data);
		while (1)
		{
			ft_hit_wall(data);
			step_forward(data);
			if (data->ver_hit && data->hor_hit)
				break ;
		}
		data->img->len[i] = calc_ray_len(data);
		data->img->len[i] = data->img->len[i] * cos(data->ray_or - data->p_a);
		data->img->hit_dir[i] = data->hit_dir;
		data->img->cl_x[i] = data->cl_x;
		data->img->cl_y[i] = data->cl_y;
		draw_ray(data, i);
		data->ray_or -= data->step_angle;
		i++;
	}
	render_map(data);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
