/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:58 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 17:22:30 by mmeier           ###   ########.fr       */
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
	char			**map;
	char			**clone_map;
	char			*file_cnt;
	char			**file_arr; // tmp variable 
	int				wall_check;
	struct s_img 	*img;
}	data;

typedef struct s_img
{
	struct s_data	*data;
	char 			*no;
	char 			*so;
	char 			*ea;
	char 			*we;
	int 			*floor;
	int 			*ceiling;

}	img;

/*						utils.c								*/

int		cube_it(char *av, data *data, img *img);
int		store_file_content(char *av, data *data);
void	init_data(data *data, img *img);
char	*ft_read_map(int fd);

/*						map_checking.c						*/

int		map_checker (data *data);	
int		err_msg(int err_flag);
char	**ft_copy_map(char **map, data *data);

/*						free.c								*/

int		free_input(data *data);
void	free_arr(char ***arr);
void	free_str(char **str);
char	**free_arr_rev(char ***av, int i);

/*						texture.c							*/

void	texture_extract(data *data, img *img);

/*						flood_fill.c						*/

int		no_closed_walls(data *data);

/*						utils_to_be_deleted.c				*/

void	print_arr(char **arr);

#endif
