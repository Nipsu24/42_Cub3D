/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/25 13:48:17 by lstorey          ###   ########.fr       */
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

static void file_splitter(data *data)
{
	data->map = ft_split(data->file_cnt, '\n');
	if (!data->map)
		return ;
}

/*this is basically the main funtion, this can get more
cluttered and we can keep the main tight*/
int	cube_it(char *av , data *data, img *img)
{	
	store_file_content(av, data);
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
		perror("Error. File could not be opened\n.");
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
  passed to function.*/
int	err_msg(int err_flag)
{
	if (err_flag == 0)
	{
		printf("Error. Empty line(s) in map.\n");
		return (1);
	}
	if (err_flag == 1)
	{
		printf("Error. Map not rectangular.\n");
		return (1);
	}
	if (err_flag == 2)
	{
		printf("Error. Invalid characters in map.\n");
		return (1);
	}
	if (err_flag == 3)
	{
		printf("Error. Player not surrounded by walls.\n");
		return (1);
	}
	return (0);
}
