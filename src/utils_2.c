/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:31 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/18 11:42:23 by lstorey          ###   ########.fr       */
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
	printf("Error.\nincorrect argument\n");
	sleep(1);
	printf(".....\n");
	sleep(2);
	printf("you idiot\n");
	sleep(2);
}
