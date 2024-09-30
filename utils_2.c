/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:40:44 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/30 10:42:43 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Prints dedicated error message depending on err_flag
  passed to function and returns 1.*/
int	err_msg(int err_flag)
{
	if (err_flag == 0)
		printf("Error.\nEmpty line(s) in map.\n");
	if (err_flag == 1)
		printf("Error.\nMultiple similar players in map or no player at all.\n");
	if (err_flag == 2)
		printf("Error.\nInvalid characters in map.\n");
	if (err_flag == 3)
		printf("Error.\nPlayer not surrounded by walls.\n");
	if (err_flag == 4)
		printf("Error.\nFloor or ceiling colour out of range.\n");
	if (err_flag == 5)
		printf("Error.\nMalloc error.\n");
	return (1);
}
