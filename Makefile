# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:57:20 by lstorey           #+#    #+#              #
#    Updated: 2024/09/26 17:37:00 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

SRC_DIR = ./
OBJ_DIR = obj
LIBFT = ./libft
LIBMLX = ./MLX42

HEADERS = -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

FILES = utils.c \
		main.c \
		map_checking.c \
		free.c \
		texture_info.c \
		flood_fill.c \
		utils_to_be_deleted.c # DO NOT DELETE!!

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

ifeq ($(wildcard $(LIBMLX)/build/libmlx42.a),)
BUILD_LIBMLX = libmlx
else
BUILD_LIBMLX =
endif

all: $(BUILD_LIBMLX) $(NAME)

$(LIBMLX):
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJ_FILES) $(LIBFT) $(LIBMLX)/build/libmlx42.a
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) $(LIBS) $(HEADERS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft
	@echo "\033[32m$(NAME) has been built successfully!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)cub3D.h | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
