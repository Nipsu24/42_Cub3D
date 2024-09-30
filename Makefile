# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:57:20 by lstorey           #+#    #+#              #
#    Updated: 2024/09/30 10:47:09 by lstorey          ###   ########.fr        #
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

FILES = utils.c\
		utils_2.c\
		main.c\
		map_checking.c\
		free.c\
		texture_info.c\
		texture_info_utils.c\
		flood_fill.c\
		map_utils.c\
		utils_to_be_deleted.c
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

ifeq ($(wildcard $(LIBMLX)/build/libmlx42.a),)
BUILD_LIBMLX = libmlx
else
BUILD_LIBMLX =
endif

all: $(BUILD_LIBMLX) $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJ_FILES) $(LIBFT) $(BUILD_LIBMLX)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) $(LIBS)  $(HEADERS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft
	@echo "\033[32m$(NAME) has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) -L$(LIBFT)  $(LIBS) -lft -g -fsanitize=address -static-libsan 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)cub3D.h | $(OBJ_DIR) 
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)
	

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -rf $(LIBMLX)/build

re: 
	make fclean 
	make all

.PHONY: all clean fclean re libmlx