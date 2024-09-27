/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:59 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/26 14:58:59 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_north(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->no = ft_substr(address, i, ft_strlen(address) - i);
}

void get_east(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->ea = ft_substr(address, i, ft_strlen(address) - i);
}

void get_south(char *address, t_img *img)
{
	int i;
	
	i = 2;
	while (address[i] == ' ')
		i++;
	img->so = ft_substr(address, i, ft_strlen(address) - i);
}

void get_west(char *address, t_img *img)
{
	int i;

	i = 2;
	while (address[i] == ' ')
		i++;
	img->we = ft_substr(address, i, ft_strlen(address) - i);
}
