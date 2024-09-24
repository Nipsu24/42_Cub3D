/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:58 by lstorey           #+#    #+#             */
/*   Updated: 2024/09/24 10:54:31 by mmeier           ###   ########.fr       */
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

/*					utils.c						*/
void	cube_it(char *av, data *data);
int		store_file_content(char *av, data *data);
void	init_data(data *data);
char	*ft_read_map(int fd);

/*					map_checking.c					*/
int		map_checker (data *data);

/*					free.c					*/
int		free_input(data *data);
void	free_arr(char ***arr);
void	free_str(char **str);

/*					utils_to_be_deleted.c			*/
void	print_arr(char **arr);

#endif
