/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:13:44 by lstorey           #+#    #+#             */
/*   Updated: 2024/11/15 14:39:39 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static int	error_n_free(char **arr)
{
	free_arr(&arr);
	return (err_msg(8));
}

static int	butter_robot(char *address, int i)
{
	int	c;

	c = 0;
	while (address[i])
	{
		if (address[i] == ',')
			c++;
		if (!ft_isdigit(address[i]) && address[i] != ','
			&& address[i] != ' ' && address[i] != '-' && address[i] != '+')
			return (1);
		i++;
	}
	return (c);
}

static int	check_for_digits(char **tmp_arr)
{
	int	j;
	int	i;
	int	digit_flag;

	j = 0;
	i = 0;
	digit_flag = 0;
	while (tmp_arr[j])
	{
		i = 0;
		digit_flag = 0;
		while (tmp_arr[j][i])
		{
			if (ft_isdigit(tmp_arr[j][i]))
				digit_flag = 1;
			if ((tmp_arr[j][i] == '+' || tmp_arr[j][i] == '-') &&
					(!ft_isdigit(tmp_arr[j][i + 1])))
				return (0);
			i++;
		}
		if (digit_flag == 0)
			return (0);
		j++;
	}
	return (1);
}

int	get_c(char *address, t_img *img, int i, int c)
{
	char	**tmp_arr;

	tmp_arr = NULL;
	address++;
	if (img->c_flag == 1)
		return (err_msg(11));
	c = butter_robot(address, i);
	if (c != 2 || number_count(address))
		return (err_msg(8));
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr || !tmp_arr[0] || !tmp_arr[1] || !tmp_arr[2])
		return (error_n_free(tmp_arr));
	if (!check_for_digits(tmp_arr))
		return (error_n_free(tmp_arr));
	img->ceiling[0] = ft_atol(tmp_arr[0]);
	img->ceiling[1] = ft_atol(tmp_arr[1]);
	img->ceiling[2] = ft_atol(tmp_arr[2]);
	if (arr_check(img->ceiling))
		return (error_n_free(tmp_arr));
	free_arr(&tmp_arr);
	img->c_flag = 1;
	return (0);
}

int	get_f(char *address, t_img *img, int i, int c)
{
	char	**tmp_arr;

	tmp_arr = NULL;
	address++;
	if (img->f_flag == 1)
		return (err_msg(11));
	c = butter_robot(address, i);
	if (c != 2 || number_count(address))
		return (err_msg(8));
	tmp_arr = ft_split(address, ',');
	if (!tmp_arr || !tmp_arr[0] || !tmp_arr[1] || !tmp_arr[2])
		return (error_n_free(tmp_arr));
	if (!check_for_digits(tmp_arr))
		return (error_n_free(tmp_arr));
	img->floor[0] = ft_atol(tmp_arr[0]);
	img->floor[1] = ft_atol(tmp_arr[1]);
	img->floor[2] = ft_atol(tmp_arr[2]);
	if (arr_check(img->floor))
		return (error_n_free(tmp_arr));
	free_arr(&tmp_arr);
	img->f_flag = 1;
	return (0);
}
