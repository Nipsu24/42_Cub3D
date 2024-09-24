/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:31:59 by lstorey           #+#    #+#             */
/*   Updated: 2024/01/26 10:42:19 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("txt.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
		line++;
	}
	free(line);
	return (0);
}
