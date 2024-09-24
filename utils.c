/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:05:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/24 10:26:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void file_splitter(data *data)
{
	data->map = ft_split(data->file_cnt, '\n');
}

/*this is basically the main funtion, this can get more
cluttered and we can keep the main tight*/
void	cube_it(char *av , data *data)
{
		store_file_content(av, data);
		file_splitter(data);
		//data->map = map_checker(data);

}

/*Initialises variables of the main data struct.*/
void	init_data(data *data)
{
	data->map = NULL;
	data->clone_map = NULL;
	data->file_cnt = NULL;
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
