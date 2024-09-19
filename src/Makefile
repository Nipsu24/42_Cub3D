# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:57:20 by lstorey           #+#    #+#              #
#    Updated: 2024/09/19 14:09:10 by lstorey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

SRC         = main.c/

OBJ         = $(SRC:.c=.o)

LIBFT       = libft/libft.a
MLX42_DIR   = ./MLX42
MLX42_LIBS  = $(MLX42_DIR)/build/libmlx42.a
CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror -Wunreachable-code #-g -fsanitize=address
OPT_FLAGS   = -Ofast
HEADER		= MLX42/include/MLX42/MLX42.h

all				: $(NAME)

$(MLX42_LIBS)	: 
					@cd MLX42 && cmake -B build && cmake --build build -j4
					@echo "made MLX42"

$(NAME)			: $(OBJ) $(MLX42_LIBS)
					make -C ./libft
					$(CC) $(CFLAGS) $(OPT_FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX42_LIBS) -lglfw -L$(GLFW) -ldl -pthread -lm -I $(HEADER)


clean			:
					make clean -C libft
					$(RM) $(OBJ)

fclean			: clean
					make fclean -C libft
					$(RM) $(NAME)
					$(RM) -r $(MLX42_DIR)/build

re				: fclean all
					@echo "re-made"

#bonus			:
.PHONY: all clean fclean re 