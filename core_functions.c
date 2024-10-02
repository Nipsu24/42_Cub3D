/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/02 14:51:17 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Checks whether file name extension (.cub) is correctly written*/
static int	file_format(char *str)
{
	char	*format;
	int		len_str;
	int		len_format;

	format = ".cub";
	len_str = ft_strlen(str);
	len_format = 4;
	if (len_str <= len_format
		|| (ft_strncmp(str + len_str - len_format, format, len_format) != 0))
	{
		printf("Error.\nInvalid filename.\n");
		return (1);
	}
	else
		return (0);
}

/*Reads content of the file (given as an arguement) and
  stores it in file_cnt string for further processing.*/
static  int	store_file_content(char *av, t_data *data)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		perror("Error.\nFile could not be opened.\n");
		close(fd);
		return (1);
	}
	data->file_cnt = ft_read_map(fd);
	if (!data->file_cnt)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	map_parsing(char *av, t_data *data, t_img *img)
{
	if (file_format(av))
		return (1);
	if (store_file_content(av, data))
		return (1);
	// print_arr(data->map);// gonna go...
	if (arr_splitter(data))
		return (1);
	if (texture_extract(data, img, 0, -1))
		return (1);
	if (map_extract(data))
		return (1);
	// info_printer(img); // to be deleted...
	// map_printer(data); // to be deleted...
	if (map_checker(data))
		return (1);
	return (0);
}

/*this is basically the main funtion, this can get more
cluttered and we can keep the main tight*/
int	cube_it(char *av, t_data *data, t_img *img)
{	
	if (map_parsing(av, data, img))
		return (1);
	// mlx_funtions(data, img); //we can start the MLX processes in here, just to break up this funtion a bit
	return (0);
}
