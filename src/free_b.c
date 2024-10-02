/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:50:15 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/02 15:31:11 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

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
