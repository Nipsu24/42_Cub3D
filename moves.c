/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/05 17:15:30 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Below 4 functions which handle the moves in 4 directions (up, down, left, right).
  Length of move is set by 'steps' (defined in header). 
  The values buf_lu (left/up) and buf_rd (right/down) (defined in header)
  are needed to avoid that the player is visually 'glitching' into the wall.
  If a move is possible, the position from which the player moves is set to '0'
  and the position to which the player moves is set to the respective sign of the
  direction the player is facing (N,E,S,W). This is needed, as at the end of each 
  move function the build_map function is called again to draw the map with 
  the updated values. All values need to be typecasted to int, as player position
  is initialised as float, which is in turn not a valid data type for the map
  indexes.*/
void	move_up(t_data *data)
{
	if (data->map[(int)(data->y_p - steps - buf_lu)][(int)data->x_p] != '1')
	{
		data->map[(int)(data->y_p - steps)][(int)data->x_p]
		= data->map[(int)data->y_p][(int)data->x_p];
		data->map[(int)data->y_p][(int)data->x_p] = '0';
		data->y_p -= steps;
		build_map(data);
	}
}

void	move_down(t_data *data)
{
	if (data->map[(int)(data->y_p + steps + buf_rd)][(int)data->x_p] != '1')
	{
		data->map[(int)(data->y_p + steps)][(int)data->x_p]
		= data->map[(int)data->y_p][(int)data->x_p];
		data->map[(int)data->y_p][(int)data->x_p] = '0';
		data->y_p += steps;
		build_map(data);
	}
}

void	move_left(t_data *data)
{
	if (data->map[(int)data->y_p][(int)(data->x_p - steps - buf_lu)] != '1')
	{
		data->map[(int)data->y_p][(int)(data->x_p - steps)]
		= data->map[(int)data->y_p][(int)data->x_p];
		data->map[(int)data->y_p][(int)data->x_p] = '0';
		data->x_p -= steps;
		build_map(data);
	}
}

void	move_right(t_data *data)
{
	if (data->map[(int)data->y_p][(int)(data->x_p + steps + buf_rd)] != '1')
	{
		data->map[(int)data->y_p][(int)(data->x_p + steps)]
		= data->map[(int)data->y_p][(int)data->x_p];
		data->map[(int)data->y_p][(int)data->x_p] = '0';
		data->x_p += steps;
		build_map(data);
	}
}
