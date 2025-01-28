/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:31 by lstorey           #+#    #+#             */
/*   Updated: 2025/01/28 11:26:09 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	number_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			c++;
			while (ft_isdigit(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	if (c > 3)
		return (1);
	return (0);
}

/*Populates player angle variable with initial angle value 
  depending on the initial direction of the player in the map */
void	check_init_pl_angle(t_data *data)
{
	if (data->p_dir == 'N')
		data->p_a = PI / 2;
	else if (data->p_dir == 'E')
		data->p_a = 2 * PI;
	else if (data->p_dir == 'S')
		data->p_a = 3 * PI / 2;
	else if (data->p_dir == 'W')
		data->p_a = PI;
	data->p_dx = cos(data->p_a);
	data->p_dy = sin(data->p_a);
}

void	official_exit(void)
{
	printf("Error.\nIncorrect argument\n");
	printf("Pass a valid map e.g. 'valid_maps/high_res.cub' as argument to the program.\n");
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

int	zero_finder(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
