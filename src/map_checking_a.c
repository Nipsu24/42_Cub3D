/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:23:52 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/11 11:38:01 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Checks if there are strings in the map that only
  consists of spaces. If this is the case, error
  message is returned.*/
static int	only_spaces_str(t_data *data)
{
	int	j;
	int	flag_no_space;
	int	i;

	j = -1;
	i = -1;
	flag_no_space = 0;
	while (data->map[++j])
	{
		flag_no_space = 0;
		i = -1;
		while (data->map[j][++i])
		{
			if (data->map[j][i] != ' ')
				flag_no_space = 1;
		}
		if (flag_no_space == 0)
			return (err_msg(0));
	}
	return (0);
}

/*Turns spaces within the map into 1's*/
static int	space_to_one(t_data *data)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (data->map[j][i] == ' ')
				data->map[j][i] = '1';
		}
	}
	return (0);
}

/*Checks if there are any characters apart from the valid ones
  in the map or if multiple identical/similar characters are present.*/
static int	invalid_chars(t_data *data)
{
	int	j;
	int	i;
	int	count;

	j = -1;
	i = -1;
	count = 0;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (data->map[j][i] != '0' && data->map[j][i] != '1'
				&& data->map[j][i] != 'W' && data->map[j][i] != 'N'
				&& data->map[j][i] != 'E' && data->map[j][i] != 'S'
				&& data->map[j][i] != ' ')
				return (err_msg(2));
			if (data->map[j][i] == 'W' || data->map[j][i] == 'N'
				|| data->map[j][i] == 'E' || data->map[j][i] == 'S')
				count++;
		}		
	}
	if (count > 1 || count == 0)
		return (err_msg(1));
	return (0);
}

/*Counts size of lenght and biggest width of the map and returns error message
  in case len of 100 and width of 200 are exceeded.*/
static int	map_size(t_data *data)
{
	int	width_1;
	int	width_2;
	int	j;

	width_1 = 0;
	width_2 = 0;
	j = -1;
	data->height = count_lines_arr(data->map);
	width_1 = ft_strlen(data->map[j + 1]);
	if (data->map[j + 2])
	{
		j = 0;
		while (data->map[++j])
		{
			width_2 = ft_strlen(data->map[j]);
			if (width_2 > width_1)
				width_1 = width_2;
		}
	}
	data->width = width_1;
	if (width_1 > 100 || width_1 < 3)
		return (err_msg(6));
	if (data->height > 100 || data->height < 3)
		return (err_msg(7));
	return (0);
}

/*Contains several error checks for the map layout.*/
int	map_checker(t_data *data)
{
	if (check_float_n(data))
		return (1);
	if (!data->map || !data->map[0])
	{
		printf("Error.\nInvalid map.\n");
		return (free_input(data));
	}
	if (map_size(data))
		return (1);
	if (only_spaces_str(data))
		return (1);
	if (invalid_chars(data))
		return (1);
	if (no_closed_walls(data))
		return (1);
	if (space_to_one(data))
		return (1);
	return (0);
}
