/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:20:35 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/31 11:46:19 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Creates a copy of a 2d array (in this project e.g. of the map array).
  This is used as map data needs to be manipulated within the
  flood fill function.*/
static char	**ft_copy_arr(char **arr)
{
	int		i;
	int		j;
	char	**clone_arr;

	i = 0;
	j = 0;
	clone_arr = NULL;
	while (arr[j])
		j++;
	clone_arr = (char **) malloc (sizeof(char *) * (j + 1));
	if (!clone_arr)
		return (NULL);
	while (arr[i])
	{
		clone_arr[i] = ft_strdup(arr[i]);
		if (!clone_arr[i])
			return (free_arr_rev(&clone_arr, i));
		i++;
	}
	clone_arr[i] = NULL;
	return (clone_arr);
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
int	count_lines_arr(char **arr)
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
static int	fill_map(char ***map, int x, int y, t_data *data)
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

static int check_map(char **map, t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (!fill_map(&data->clone_map, x, y, data))
				{
					free_arr(&data->clone_map);
					err_msg(3);
					return (0);
				}
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

static int zero_finder(char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
				return(1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

/*First determines player's position. Then populates map_clone
  variable with map data. Passes then this data to flood fill
  function in order to check if player is surrounded by walls.
  If this is not the case, fill_map returns 0 (=>'if !fill_map)'.*/
int	no_closed_walls(t_data *data)
{
	int	p_pos_x;
	int	p_pos_y;

	p_pos_x = 0;
	p_pos_y = 0;
	player_pos(data->map, &p_pos_x, &p_pos_y);
	data->y_p = p_pos_y;
	data->x_p = p_pos_x;
	data->p_dir = data->map[p_pos_y][p_pos_x];
	data->clone_map = ft_copy_arr(data->map);
	if (!data->clone_map)
		return (1);
	if (!fill_map(&data->clone_map, p_pos_x, p_pos_y, data))
	{
		free_arr(&data->clone_map);
		return (err_msg(3));
	}
	while (zero_finder(data->clone_map))
	{
		if (!check_map(data->clone_map, data))
			return (1);
	}
	free_arr(&data->clone_map);
	return (0);
}
