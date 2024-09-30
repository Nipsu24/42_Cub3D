/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:40:44 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/30 14:22:23 by mmeier           ###   ########.fr       */
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
	if (err_flag == 6)
		printf("Error.\nMap consists of too many colums.\n");
	if (err_flag == 7)
		printf("Error.\nMap consists of too many lines.\n");
	return (1);
}
