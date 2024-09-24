/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:23:52 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 11:30:55 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	only_spaces_str(data *data)
{
	int	j;

	j = -1;
	while (j++, data->map[j])
	{
		
	}
	return (1);
}

int	map_checker (data *data)
{
	if (only_spaces_str(data))
		return (free_input(data));

	return (0);
}
