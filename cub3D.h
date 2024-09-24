/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:58 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 10:17:17 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_data
{
	char	**map;
	char	**clone_map;
	char	*file_cnt;
	struct s_img 	*img;
}	data;

typedef struct s_img
{
	data *data;
	char *no;
	char *so;
	char *ea;
	char *we;
	int *floor;
	int *ceiling;

}	img;

/*					utils.c						*/
void	cube_it(char *av, data *data);
int		store_file_content(char *av, data *data);
void	init_data(data *data);
char	*ft_read_map(int fd);

/*					map_checking.c					*/
char	**map_checker (data *data);


#endif
