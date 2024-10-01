/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/01 16:45:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_for_double_n_in_map(t_data *data, int i, int map_flag)
{
	if (map_flag && data->file_cnt[i])
	{
		while (data->file_cnt[i])
		{
			if (data->file_cnt[i] == '\n' && data->file_cnt[i + 1] == '\n')
			{
				printf("Error. Multiple newlines in map.\n");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

/*Iterates through initial map string and checks if there is after a newline character
  either a 1, 0 or 'space' occuring (identifiers for map). If this is the case, breaks
  out of loop and iterates further in map part of the string (in helper function) in order
  to check for double/multiple newline characters in a row*/
int	check_double_n(t_data *data)
{
	int	map_flag;
	int	i;

	map_flag = 0;
	i = 0;
	while (data->file_cnt[i])
	{
		if (data->file_cnt[i] == '\n')
		{
			if (!map_flag && (data->file_cnt[i + 1] == '1'
					|| data->file_cnt[i + 1] == '0'
					|| data->file_cnt[i + 1] == ' '))
			{
				map_flag = 1;
				break ;
			}
		}
		i++;
	}
	if (check_for_double_n_in_map(data, i, map_flag))
		return (1);
	return (0);
}

/*this is basically the main funtion, this can get more
cluttered and we can keep the main tight*/
int	cube_it(char *av, t_data *data, t_img *img)
{	
	if (file_format(av))
		return (1);
	if (store_file_content(av, data))
		return (1);
	// file_splitter(data); //only for map testing purpose
	// print_arr(data->map);// gonna go...
	if (arr_splitter(data))
		return (1);
	if (texture_extract(data, img, 0, -1))
		return (1);
	if (map_extract(data))
		return (free_input(data));
	info_printer(img); // to be deleted...
	map_printer(data); // to be deleted...
	if (check_double_n(data))
		return (1);
	if (map_checker(data))
		return (1);
	// mlx_funtions(data, img); //we can start the MLX processes in here, just to break up this funtion a bit
	return (0);
}

int	file_format(char *str)
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

/*Initialises variables of the main data struct.*/
void	init_data(t_data *data, t_img *img)
{
	data->map = NULL;
	data->clone_map = NULL;
	data->file_cnt = NULL;
	data->file_arr = NULL;
	img->no = NULL;
	img->so = NULL;
	img->ea = NULL;
	img->we = NULL;
	data->wall_check = 0;
	data->x_p = 0;
	data->y_p = 0;
	data->mlx = NULL;
}

/*Reads content of the file (given as an arguement) and
  stores it in file_cnt string for further processing.*/
int	store_file_content(char *av, t_data *data)
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

/*Reads entire map content until NULL-Terminator*/
char	*ft_read_map(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		count;
	char	*str;

	count = 1;
	str = NULL;
	while (count > 0)
	{
		count = read (fd, buf, BUFFER_SIZE);
		if (!str && count == 0)
			return (ft_free(&str));
		if (count == -1)
			return (ft_free(&str));
		buf[count] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_gnl_strjoin(str, buf);
		if (!str)
			return (ft_free(&str));
	}
	return (str);
}
