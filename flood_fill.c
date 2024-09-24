/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:20:35 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/24 17:32:17 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Creates a copy of 2d arrays (in this project of the map array).
  This is used as map data needs to be manipulated within the
  flood fill function.*/
static char	**ft_copy_map(char **map, data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
		j++;
	data->clone_map = (char **) malloc (sizeof(char *) * (j + 1));
	if (!data->clone_map)
		return (NULL);
	while (map[i])
	{
		data->clone_map[i] = ft_strdup(map[i]);
		if (!data->clone_map[i])
			return (free_arr_rev(&data->clone_map, i));
		i++;
	}
	data->clone_map[i] = NULL;
	return (data->clone_map);
}

/*Determines player's position within a map.*/
static void	player_pos(char **map, int *x, int *y)
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

/*Counts amount of lines in a 2d array.*/
static int	count_lines_arr(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
		j++;
	return (j);
}

/*Checks first height of map and current line's width in order
  to know the boundaries of map. Returns 0 if boundaries are
  hit/exceeded, returns 1 if hits 1 or X.*/
static int	fill_map(char ***map, int x, int y, data *data)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	height = count_lines_arr(data->map);
	if (y < 0 || y >= height)
		return (0);
	width = ft_strlen((*map)[y]);
	if (x < 0 || x >= width)
		return (0);
	if ((*map)[y][x] == '1' || (*map)[y][x] == 'X')
		return (1);
	(*map)[y][x] = 'X';
	if (!fill_map(map, x + 1, y, data))
		return (0);
	if (!fill_map(map, x - 1, y, data))
		return (0);
	if (!fill_map(map, x, y + 1, data))
		return (0);
	if (!fill_map(map, x, y - 1, data))
		return (0);
	return (1);
}

/*First determines player's position. Then populates map_clone
  variable with map data. Passes then this data to flood fill
  function in order to check if player is surrounded by walls.
  If this is not the case, fill_map returns 0 (=>'if !fill_map)'.*/
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
	if (!ft_copy_map(data->map, data))
		return (1);
	if (!fill_map(&data->clone_map, p_pos_x, p_pos_y, data))
	{
		free_arr(&data->clone_map);
		return (err_msg(3));
	}
	free_arr(&data->clone_map);
	return (0);
}
