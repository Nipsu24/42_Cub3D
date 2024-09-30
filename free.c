/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:15 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/30 15:34:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Frees all relevant data allocated for the project. Returns 1
  if return val is set to 1. If set to 0, returns 0.*/
int	free_all(t_data *data, t_img *img, int return_val)
{
	free_arr(&data->map);
	free_str(&data->file_cnt);
	free_arr(&data->file_arr);
	free_dir(img);
	if (return_val)
		return (1);
	else
		return (0);
}


/*Frees related input variables in case map parameters
  are invalid. Quits with 1.*/
int	free_input(t_data *data)
{
	free_arr(&data->map);
	free_str(&data->file_cnt);
	free_arr(&data->file_arr);
	return (1);
}

int	free_dir(t_img *img)
{
	free_str(&img->no);
	free_str(&img->ea);
	free_str(&img->we);
	free_str(&img->so);
	return (1);
}


/*Frees 2d arrays and sets it to NULL. Caller function
  should pass address of array to this function.*/
void	free_arr(char ***arr)
{
	int	j;

	j = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[j])
	{
		free((*arr)[j]);
		(*arr)[j] = NULL;
		j++;
	}
	free(*arr);
	*arr = NULL;
}

/*Frees string and sets pointer to NULL. Caller function
  should pass address of str to this function.*/
void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

/*Frees array in reverse (e.g. if allocation for string
  within array fails) and sets it to NULL.*/
char	**free_arr_rev(char ***av, int i)
{
	if (*av == NULL)
		return (NULL);
	while (i > 0)
	{
		free((*av)[i - 1]);
		(*av)[i - 1] = NULL;
		i--;
	}
	free(*av);
	*av = NULL;
	return (NULL);
}
