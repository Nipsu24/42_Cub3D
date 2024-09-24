/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:23:52 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 16:06:09 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Checks if there are strings in the map that only
  consists of spaces. If this is the case, error
  message is returned.*/
static int	only_spaces_str(data *data)
{
	int	j;
	int	flag_no_space;
	int	i;

	j = -1;
	i = -1;
	flag_no_space = 0;
	while (j++, data->map[j])
	{
		flag_no_space = 0;
		i = 0;
		while (i++, data->map[j][i])
		{
			if (data->map[j][i] != ' ')
				flag_no_space = 1;
		}
		if (flag_no_space == 0)
			return (err_msg(0));
	}
	return (0);
}

/*Checks if all strings in the map array have the same lenght.
  Returns 1 if this is not the case.*/
// static int	not_rectangular(data *data)
// {
// 	int	j;
// 	int	len_a;
// 	int	len_b;
// 	int	i;

// 	j = -1;
// 	i = -1;
// 	len_a = 0;
// 	len_b = 0;
// 	len_a = ft_strlen(data->map[0]);
// 	while (j++, data->map[j])
// 	{
// 		len_b = ft_strlen(data->map[j]);
// 		if (len_a != len_b)
// 			return (err_msg(1));
// 	}
// 	return (0);
// }

/*Turns spaces within the map into 1's*/
static int	space_to_one(data *data)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (j++, data->map[j])
	{
		i = 0;
		while (i++, data->map[j][i])
		{
			if (data->map[j][i] == ' ')
				data->map[j][i] = '1';
		}
	}
	return (0);
}

static int	wrong_characters(data *data)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (j++, data->map[j])
	{
		i = 0;
		while (i++, data->map[j][i])
		{
			if (data->map[j][i] != '0' && data->map[j][i] != '1'
				&& data->map[j][i] != 'W' && data->map[j][i] != 'N'
				&& data->map[j][i] != 'E' && data->map[j][i] != 'S'
				&& data->map[j][i] != ' ')
				return (err_msg(2));
		}		
	}
	return (0);
}

void	player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'E'
				|| map[j][i] == 'S' || map[j][i] == 'W')
			{
				*x = i;
				*y = j;
			}
			i++;
		}
		j++;
	}
}

int	no_closed_walls(data *data)
{
	int	p_pos_x;
	int	p_pos_y;
	int	i;
	int	j;

	p_pos_x = 0;
	p_pos_y = 0;
	i = 0;
	j = 0;
	player_pos(data->map, &p_pos_x, &p_pos_y);
	fill_map(&map_2d, p_pos_x, p_pos_y);
	while (map_2d[i])
	{
		j = 0;
		while (map_2d[i][j])
		{
			if (map_2d[i][j] == 'E' || map_2d[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


int	map_checker(data *data)
{
	if (!data->map || !data->map[0])
	{
		printf("Error. Empty map.\n");
		return (free_input(data));
	}
	if (only_spaces_str(data))
		return (free_input(data));
	// if (not_rectangular(data))
	// 	return (free_input(data));
	if (space_to_one(data))
		return (free_input(data));
	if (wrong_characters(data)) // double characters to be handled, too
		return (free_input(data));
	if (no_closed_walls(data))
		return (free_input(data));
	print_arr(data->map);
	return (0);
}
