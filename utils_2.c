/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:40:44 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/01 16:32:19 by mmeier           ###   ########.fr       */
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
	if (err_flag == 8)
		printf("Error.\nInvalid '.cub' file.\n");
	if (err_flag == 9)
		printf("Error.\nCeiling or floor value out of scope.\n");
	return (1);
}

int arr_splitter(t_data *data)
{
	static int i = 0;
	
	while(data->file_cnt[i])
	{
		if (data->file_cnt[i] == ' ' && data->file_cnt[i + 1] == '\n')
		{
			free_str(&data->file_cnt);
			err_msg(8);
			return (1);
		}	
		i++;
	}
	data->file_arr = ft_split(data->file_cnt, '\n');
	if (!data->file_arr)
		return (1);
	return (0);
}

/*Helper function of ft_atol, protects int max overflow by looping
  only until 11 digit.*/
static long	ft_convertno(const char *str, int n)
{
	long int	number;
	int			count;

	number = 0;
	count = 0;
	while (str[n] >= 48 && str[n] <= 57 && count < 11)
	{
		number *= 10;
		number += str[n] - 48;
		n++;
		count++;
	}
	return (number);
}

long int	ft_atol(const char *str)
{
	int			i;
	int			minus;
	long int	number;
	int			plus;

	minus = 0;
	plus = 0;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		if (str[i] == '+')
			plus++;
		if (minus + plus > 1)
			return (0);
		i++;
	}
	number = ft_convertno(str, i);
	if (minus == 1)
		return (-number);
	return (number);
}
