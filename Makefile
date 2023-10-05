# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/29 23:49:19 by ljerinec          #+#    #+#              #
#    Updated: 2023/10/05 12:30:56 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SOURCES =	sources/main.c \
			sources/parsing/simple_parsing.c \
			sources/parsing/map_parsing.c \
			sources/parsing/parsing_utils.c \
			sources/engine/minimap.c \
			sources/engine/minimap_utils.c \
			sources/engine/player.c \
			sources/engine/player_movement.c \

OBJ_DIR = object/
OBJECTS = $(SOURCES:.c=.o)

CUB3D = cub3d

LIBFT_DIR = includes/libft/libft.a
FT_PRINTF_DIR = includes/ft_printf/ft_printf.a
INCLUDES_DIR = includes/
MLX42_INC = -lglfw -L /Users/ljerinec/.brew/Cellar/glfw/3.3.8/lib/
# MLX42_INC = -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib
MLX42_DIR = MLX42/build/libmlx42.a

####################COMPILATION STYLING####################

TOTAL_FILES = $(words $(SOURCES))
CURRENT_FILE = 0
BAR_WIDTH = 30

PRINT_NAME		:= cub3d
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

all: $(CUB3D)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(BAR_WIDTH) / $(TOTAL_FILES)))))
	@$(eval REMAINING=$(shell echo $$(($(BAR_WIDTH) - $(PROGRESS)))))

	@printf "$(PRINT_PREFIX) \033[1;33m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "]\r\033[0m"

$(CUB3D): $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling MLX42 \033[0m\n"
	@cmake MLX42 -B MLX42/build
	@cmake --build MLX42/build -j4
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"
	@make -C includes/libft
	@$(CC) $(CFLAGS) -o $(CUB3D) $(OBJECTS) $(MLX42_DIR) $(MLX42_INC) $(LIBFT_DIR) $(FT_PRINTF_DIR)
	@printf "$(PRINT_PREFIX) \033[1;32m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "][OK]\n\033[0m"

clean:
	@make -C includes/libft clean
	@rm -f $(OBJECTS)
	@rm -f *.o
	@rm -f */*.o
	@rm -f */*/*.o

fclean: clean
	@make -C includes/libft fclean
	@rm -f $(CUB3D)
	@rm -f "minishell *"

re: fclean all

.PHONY: all clean fclean re
