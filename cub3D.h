/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:58 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/01 16:39:04 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h> //maybe delete

typedef struct s_data
{
	char			**map;
	char			**clone_map;
	char			*file_cnt;
	char			**file_arr;
	int				wall_check;
	mlx_t			*mlx;
	int				x_p;
	int				y_p;
	struct s_img	*img;
}	t_data;

typedef struct s_img
{
	struct s_data	*data;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	long int				floor[3];
	long int				ceiling[3];

}	t_img;

/*						utils.c								*/

int		cube_it(char *av, t_data *data, t_img *img);
int		store_file_content(char *av, t_data *data);
void	init_data(t_data *data, t_img *img);
char	*ft_read_map(int fd);
int		file_format(char *str);
int		check_double_n(t_data *data);

/*						utils_2.c								*/

int			err_msg(int err_flag);
int 		arr_splitter(t_data *data);
long int	ft_atol(const char *str);

/*						mlx_functions.c						*/

// void 	mlx_funtions(t_data *data, t_img *img);

/*						map_checking.c						*/

int		map_checker (t_data *data);	
// char	**ft_copy_map(char **map, data *data);

/*						free.c								*/

int		free_all(t_data *data, t_img *img, int return_val);
int		free_input(t_data *data);
void	free_arr(char ***arr);
void	free_str(char **str);
char	**free_arr_rev(char ***av, int i);
int		free_dir(t_img *img);

/*						texture_info.c						*/

int		texture_extract(t_data *data, t_img *img, int x, int y);
int 	texture_extract_helper_1(t_data *data, int y, int x, t_img *img);
int 	get_c(char *address, t_img *img);
int 	get_f(char *address, t_img *img);
int		range_check(long int *arr);
void	check_null(t_img *img);

/*						texture_info_utils.c				*/

int 	get_north(char *address, t_img *img);
int 	get_south(char *address, t_img *img);
int 	get_east(char *address, t_img *img);
int 	get_west(char *address, t_img *img);


/*						flood_fill.c						*/

int		no_closed_walls(t_data *data);

/*						map_utils.c							*/

int		map_extract(t_data *data);
int		count_lines_arr(char **arr);

/*						utils_to_be_deleted.c				*/

void	print_arr(char **arr);
void 	info_printer(t_img *img);
void	file_splitter(t_data *data);
void 	map_printer(t_data *data);

#endif
