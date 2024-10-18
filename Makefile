# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:57:20 by lstorey           #+#    #+#              #
#    Updated: 2024/10/18 12:51:54 by lstorey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

SRC_DIR = ./
OBJ_DIR = obj
LIBFT = ./includes/libft
LIBMLX = ./includes/MLX42
INCLUDES = -I./

HEADERS = -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

FILES = src/utils.c \
		src/utils_2.c \
		src/core_functions.c \
		src/main.c\
		src/map_checking_a.c \
		src/map_checking_b.c \
		src/free_a.c \
		src/free_b.c \
		src/texture_info.c \
		src/texture_info_utils.c \
		src/flood_fill.c \
		src/map_utils.c \
		src/utils_to_be_deleted.c \
		mlx_functions.c \
		moves.c \
		draw_ray.c \
		rotate.c \
		init_images.c \
		build_mini_map.c
		
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: libmlx $(NAME)

$(LIBMLX):
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi

libmlx: $(LIBMLX)
	@if [ ! -d $(LIBMLX)/build ]; then \
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	fi

$(NAME): $(OBJ_FILES) $(LIBFT) $(LIBMLX)/build/libmlx42.a
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) $(HEADERS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) $(LIBS) -lft
	@echo "\033[32m$(NAME) has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) -L$(LIBFT) $(LIBS) $(INCLUDES) -lft -g -fsanitize=address

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)includes/cub3D.h | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(LIBFT)/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
