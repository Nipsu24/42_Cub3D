/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/25 15:07:49 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void info_printer(img *img)
{
	printf("img->no         :%s\n", img->no);
	printf("img->ea         :%s\n", img->ea);
	printf("img->so         :%s\n", img->so);
	printf("img->we         :%s\n", img->we);
	printf("img->ceiling[0] :%d\n", img->ceiling[0]);
	printf("img->ceiling[1] :%d\n", img->ceiling[1]);
	printf("img->ceiling[2] :%d\n", img->ceiling[2]);
	printf("img->floor[0]   :%d\n", img->floor[0]);
	printf("img->floor[1]   :%d\n", img->floor[1]);
	printf("img->floor[2]   :%d\n", img->floor[2]);
}

static void arr_splitter(data *data)
{
	data->file_arr = ft_split(data->file_cnt, '\n');
	if (!data->file_arr)
		return ;
}

static void	file_splitter(data *data)
{
	data->map = ft_split(data->file_cnt, '\n');
	if (!data->map)
		return ;
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

/*this is basically the main funtion, this can get more
cluttered and we can keep the main tight*/
int	cube_it(char *av, data *data, img *img)
{	
	
	if (file_format(av))
		return (1);
	if (store_file_content(av, data))
		return (1);
	file_splitter(data); //only for map testing purpose
	// print_arr(data->map);// gonna go...
	arr_splitter(data); //only for map testing purpose
	texture_extract(data, img, 0, 0);
	info_printer(img); // to be deleted...
	
	if (map_checker(data))
		return (1);
	return (0);
}

/*Initialises variables of the main data struct.*/
void	init_data(data *data, img *img)
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
}

/*Reads content of the file (given as an arguement) and
  stores it in file_cnt string for further processing.*/
int	store_file_content(char *av, data *data)
{
	int	fd;
	int	i;

	i = 0;
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
	return (1);
}
