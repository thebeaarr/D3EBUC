CC= cc
MLX_DIR = lib/minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Werror -Wextra -Iinclude -I./lib/libft -I./lib/libft/get_next_line -I$(MLX_DIR) -I./mlx_init/include -g
SRCS = $(wildcard lib/get_next_line/*.c) $(wildcard src/cub3d_parser/*.c) $(wildcard src/Raycast/*.c)  $(wildcard src/init/*.c) $(wildcard src/minimap/*.c) $(wildcard src/movements/*.c) src/main.c src/game.c

LIBFT_DIR = lib/libft
HEADER = cub3d.h
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
OBJ = $(SRCS:.c=.o)
NAME = cub3D

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ) $(HEADER)
	$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
