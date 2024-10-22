/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:06:30 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/18 13:41:57 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*BACKGROUND*/
int	create_bg_img(t_data *data)
{
	data->img->bg = mlx_new_image(data->mlx,
			screen_width * PX, screen_height * PX);
	if (!data->img->bg)
		return (1);
	return (0);
}

/*FOREGROUND*/
int	create_fg_img(t_data *data)
{
	data->img->fg = mlx_new_image(data->mlx,
			screen_width * PX, screen_height * PX);
	if (!data->img->fg)
		return (1);
	return (0);
}

/*ALL RAYS*/
int	create_ray_img(t_data *data)
{
	data->img->ray = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->ray)
		return (1);
	return (0);
}

/*Mini-map*/
// int	create_mm_img(t_data *data)
// {
// 	data->img->mm = mlx_new_image(data->mlx,
// 			screen_width/4 * PX, screen_height/4 * PX);
// 	if (!data->img->ray)
// 		return (1);
// 	return (0);
// }

/*PLAYER IMAGE*/
int	create_pl_img(t_data *data)
{
	data->img->pl = mlx_new_image(data->mlx,
			data->width * PX, data->height * PX);
	if (!data->img->pl)
		return (1);
	return (0);
}
