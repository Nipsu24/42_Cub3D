/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:59 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/03 11:06:38 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	get_north(char *address, t_img *img)
{
	int	i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->no = ft_substr(address, i, ft_strlen(address) - i);
	if (!img->no)
		return (1);
	return (0);
}

int	get_east(char *address, t_img *img)
{
	int	i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->ea = ft_substr(address, i, ft_strlen(address) - i);
	if (!img->ea)
		return (1);
	return (0);
}

int	get_south(char *address, t_img *img)
{
	int	i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->so = ft_substr(address, i, ft_strlen(address) - i);
	if (!img->so)
		return (1);
	return (0);
}

int	get_west(char *address, t_img *img)
{
	int	i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->we = ft_substr(address, i, ft_strlen(address) - i);
	if (!img->we)
		return (1);
	return (0);
}

int	range_check(long int *arr)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (arr[i] < 0 || arr[i] > 255)
			return (1);
		i++;
	}
	return (0);
}
