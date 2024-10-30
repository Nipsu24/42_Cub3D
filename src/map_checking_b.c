/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:23:52 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/28 11:01:08 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int	check_for_float_n_in_map(t_data *data, int i, int map_flag)
{
	if (map_flag && data->file_cnt[i])
	{
		while (data->file_cnt[i])
		{
			if (data->file_cnt[i] == '\n' && data->file_cnt[i + 1] == '\n')
			{
				err_msg(10);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

/*Iterates through initial map string and checks if there is after 
  a newline character either a 1, 0 or 'space' occuring (identifiers
  for map). If this is the case, breaks out of loop and iterates 
  further in map part of the string (in helper function) in order
  to check for float/multiple newline characters in a row*/
int	check_float_n(t_data *data)
{
	int	map_flag;
	int	i;

	map_flag = 0;
	i = 0;
	while (data->file_cnt[i])
	{
		if (data->file_cnt[i] == '\n')
		{
			if (!map_flag && (data->file_cnt[i + 1] == '1'
					|| data->file_cnt[i + 1] == '0'
					|| data->file_cnt[i + 1] == ' '))
			{
				map_flag = 1;
				break ;
			}
		}
		i++;
	}
	if (check_for_float_n_in_map(data, i, map_flag))
		return (1);
	return (0);
}
