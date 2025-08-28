CC = cc 
CFLAGS = -Wall -Werror -Wextra -I./libft -I./libft/get_next_line

SRCS = cub3d_parser/srcs/parser.c main/cub3d.c 

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ= $(SRCS:.c=.o)

NAME = cub3d


all : $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)


%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re