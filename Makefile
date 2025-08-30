CC = cc
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Werror -Wextra -I./libft -I./libft/get_next_line -I$(MLX_DIR)
SRCS = cub3d_parser/srcs/parser.c main/cub3d.c mlx_init/src/mlx.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
OBJ = $(SRCS:.c=.o)
NAME = cub3d

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

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
