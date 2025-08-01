CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = cub3d.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c \
       srcs/parsing/utils_n01.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)  # if you include libft headers

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
