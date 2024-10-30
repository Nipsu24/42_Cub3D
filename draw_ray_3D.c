/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/25 16:39:18 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

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
		x += (data->ray_dir_x * RAY_SPEED);
		y += (data->ray_dir_y * RAY_SPEED);
		len = sqrt((x - data->x_p) * (x - data->x_p) + (y - data->y_p) * (y - data->y_p));

		if (x < 0 || y < 0 || x >= S_WID || y >= S_HEI
			|| data->map[(int)y][(int)x] == '1')
			return (len);
	}
}
// static void init_step_side(float *side_dist_x, float *side_dist_y, int *step_x, int *step_y, t_data *data, int map_x, int map_y, float x, float y, float delta_dist_x, float delta_dist_y)
// {
// 	if (data->ray_dir_x < 0)
// 	{
// 		*step_x = -1;
// 		*side_dist_x = (x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		*step_x = 1;
// 		*side_dist_x = (map_x + 1.0 - x) * delta_dist_x;
// 	}

// 	if (data->ray_dir_y < 0)
// 	{
// 		*step_y = -1;
// 		*side_dist_y = (y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		*step_y = 1;
// 		*side_dist_y = (map_y + 1.0 - y) * delta_dist_y;
// 	}
// }


static int perform_dda(t_data *data, int *map_x, int *map_y, float *side_dist_x, float *side_dist_y, float delta_dist_x, float delta_dist_y)
{
	int side;

	while (1)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += delta_dist_x;
			if (data->ray_dir_x < 0)
				*map_x -= 1;
			else
				*map_x += 1;
			side = 0;
		}
		else
		{
			*side_dist_y += delta_dist_y;
			if (data->ray_dir_y < 0)
				*map_y -= 1;
			else
				*map_y += 1;
			side = 1;
		}
		if (data->map[*map_y][*map_x] == '1')
			return (side);
	}
}

static int determine_hit_direction(t_data *data, int side)
{
	if (side == 0)
	{
		if (data->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (data->ray_dir_y > 0)
			return (4); 
		else
			return (1);
	}
}

static int init_ray_direction(t_data *data, float angle)
{
    data->ray_dir_x = cos(angle);
    data->ray_dir_y = -sin(angle);
    return (0);
}

static void init_dda_values(float *side_dist_x, float *side_dist_y, int *step_x, int *step_y, t_data *data, int *map_x, int *map_y, float x, float y)
{
    if (data->ray_dir_x < 0)
    {
        *step_x = -1;
        *side_dist_x = (x - *map_x) * fabs(1 / data->ray_dir_x);
    }
    else
    {
        *step_x = 1;
        *side_dist_x = (*map_x + 1.0 - x) * fabs(1 / data->ray_dir_x);
    }
    
    if (data->ray_dir_y < 0)
    {
        *step_y = -1;
        *side_dist_y = (y - *map_y) * fabs(1 / data->ray_dir_y);
    }
    else
    {
        *step_y = 1;
        *side_dist_y = (*map_y + 1.0 - y) * fabs(1 / data->ray_dir_y);
    }
}

static int hit_direction(t_data *data, float angle)
{
    int map_x;
    int map_y;
    int side;
    int step_x;
    int step_y;
    float side_dist_x;
    float side_dist_y;

    map_x = (int)data->x_p;
    map_y = (int)data->y_p;
    init_ray_direction(data, angle);
    init_dda_values(&side_dist_x, &side_dist_y, &step_x, &step_y, data, &map_x, &map_y, data->x_p, data->y_p);
    side = perform_dda(data, &map_x, &map_y, &side_dist_x, &side_dist_y, fabs(1 / data->ray_dir_x), fabs(1 / data->ray_dir_y));

    return (determine_hit_direction(data, side));
}

// static int hit_direction(t_data *data, float angle) //original
// {
// 	float x = data->x_p, y = data->y_p;
// 	int map_x = (int)x; 
// 	int	map_y = (int)y;
// 	float delta_dist_x = fabs(1 / data->ray_dir_x);
// 	float	delta_dist_y = fabs(1 / data->ray_dir_y);
// 	float side_dist_x;
// 	int side_dist_y;
// 	int step_x;
// 	int step_y;

// 	data->ray_dir_x = cos(angle);
// 	data->ray_dir_y = -sin(angle);
// 	init_step_side(&side_dist_x, (float*)&side_dist_y, &step_x, &step_y, data, map_x, map_y, x, y, delta_dist_x, delta_dist_y);

// 	int side = perform_dda(data, &map_x, &map_y, &side_dist_x, (float*)&side_dist_y, delta_dist_x, delta_dist_y);
// 	return (determine_hit_direction(data, side));
// }

// static void	updating_fg(t_data *data) //ORiGINAL
// {
// 	int		ray_index;
// 	float	len;
// 	float	line_height;
// 	float	start_y;
// 	float	end_y;
// 	float	y;
// 	float	screen_center;
// 	int		pixel_x;
// 	float	angle_offset;
// 	float	fov = PI / 3;
 
// 	screen_center = S_HEI / 2;
// 	ray_index = 0;

// 	while (ray_index < RAYS)
//     {
// 		angle_offset = (ray_index - RAYS / 2) * (fov / RAYS);	
//         len = data->img->len[ray_index];
//         if (len == 0)
//             len = 0.01f;
// 		len = len * cos(angle_offset);
//         line_height = (B_HEI) / len;
//         start_y = screen_center - (line_height / 2);
//         end_y = screen_center + (line_height / 2);
//         y = start_y;
//         pixel_x = S_WID - (ray_index * (S_WID / (float)RAYS));
//         while (y <= end_y)
//         {
//             if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 1)
//                 mlx_put_pixel(data->img->fg, pixel_x, y, 0x00FFFFFF);
//             if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 2)
//                 mlx_put_pixel(data->img->fg, pixel_x, y, 0xFF00FFFF);
//             if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 3)
//                 mlx_put_pixel(data->img->fg, pixel_x, y, 0xFFFF00FF);
//             if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 4)
//                 mlx_put_pixel(data->img->fg, pixel_x, y, 0x000000FF);
//             y += 1;
//         }
//         ray_index++;
//     }
// 	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);	
// }
static void updating_fg(t_data *data)
{
    int ray_index;
    float len, line_height, y, pixel_x;
    float screen_center = S_HEI / 2;
    float angle_offset;
    float fov = PI / 3;
    float correction_factor = 0.3;  // Apply a 30% correction to reduce overcorrection

    ray_index = 0;
    while (ray_index < RAYS)
    {
        angle_offset = (ray_index - (RAYS / 2)) * (fov / RAYS);
        len = data->img->len[ray_index] * (1 - correction_factor + correction_factor * cos(angle_offset));

        // Ensure len isn't zero to avoid division issues
        if (len < 0.01f) len = 0.01f;

        line_height = B_HEI / len;
        float start_y = screen_center - (line_height / 2);
        float end_y = screen_center + (line_height / 2);
        pixel_x = S_WID - (ray_index * (S_WID / (float)RAYS));
        y = start_y;

        while (y <= end_y)
        {
            if (y >= 0 && y < S_HEI)
            {
                int color = 0;
                if (data->img->hit_dir[ray_index] == 1)
                    color = 0x00FFFFFF;
                else if (data->img->hit_dir[ray_index] == 2)
                    color = 0xFF00FFFF;
                else if (data->img->hit_dir[ray_index] == 3)
                    color = 0xFFFF00FF;
                else if (data->img->hit_dir[ray_index] == 4)
                    color = 0x000000FF;

                mlx_put_pixel(data->img->fg, pixel_x, y, color);
            }
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
	step_angle = (end_angle - start_angle) / RAYS;
	current_angle = start_angle;
	i = 0;
	while (current_angle <= end_angle && i < RAYS)
	{
		data->img->len[i] = draw_single_ray_3d(data, current_angle);
		data->img->hit_dir[i] = hit_direction(data, current_angle);
		current_angle += step_angle;
		i++;
	}
	updating_fg(data);
	// clean exit
}



