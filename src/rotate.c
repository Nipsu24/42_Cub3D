/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/05 16:52:16 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Rotates player counter-clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_left(t_data *data)
{
	data->p_a += RO_SPEED;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
}

/*Rotates player clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_right(t_data *data)
{
	data->p_a -= RO_SPEED;
	if (data->p_a <= 0)
		data->p_a += 2 * PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
}
