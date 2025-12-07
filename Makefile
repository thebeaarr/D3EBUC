CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I./lib/libft -I./lib/libft/get_next_line \
		 -I./lib/minilibx-linux -I./mlx_init/include -g

NAME = cub3D

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_FLAGS = -lmlx -lXext -lX11 -lm

SRCS_GNL = \
	lib/libft/get_next_line/get_next_line.c \
	lib/libft/get_next_line/get_next_line_utils.c

SRCS_PARSER = \
	src/cub3d_parser/color_tools.c \
	src/cub3d_parser/color_tools1.c \
	src/cub3d_parser/get_color.c \
	src/cub3d_parser/get_map.c \
	src/cub3d_parser/get_textures.c \
	src/cub3d_parser/map_check_utils.c \
	src/cub3d_parser/map_closed.c \
	src/cub3d_parser/parse_tools.c \
	src/cub3d_parser/parser.c \
	src/cub3d_parser/read_config.c \
	src/cub3d_parser/read_config_helper.c \
	src/cub3d_parser/read_file.c \
	src/cub3d_parser/texture_memory.c \
	src/cub3d_parser/texture_utils.c \
	src/cub3d_parser/tools.c \
	src/cub3d_parser/tools_1.c \
	src/cub3d_parser/tools_2.c

SRCS_FREE = \
	src/free/free_all.c


SRCS_INIT = \
	src/init/load_texutres.c \
	src/init/player_init.c \
	src/init/render_init.c


SRCS_MINIMAP = \
	src/minimap/frame.c \
	src/minimap/init.c \
	src/minimap/minimap.c \
	src/minimap/player_view.c


SRCS_MOVEMENTS = \
	src/movements/key_handling.c \
	src/movements/update_transform.c \
	src/movements/wall_collision.c

SRCS_RAYCAST = \
	src/Raycast/draw_textures.c \
	src/Raycast/draw_textures_helper.c \
	src/Raycast/raycast.c \
	src/Raycast/raycast_utils.c \
	src/Raycast/ray_init.c

SRCS_MAIN = \
	src/main.c \
	src/game.c

SRCS = $(SRCS_GNL) $(SRCS_PARSER) $(SRCS_FREE) $(SRCS_INIT) \
	   $(SRCS_MINIMAP) $(SRCS_MOVEMENTS) $(SRCS_RAYCAST) $(SRCS_MAIN)

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)


$(NAME): $(LIBFT)  $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	make all

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
