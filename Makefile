CC=cc

CFLAGS= -Wall -Werror -Wextra  -g

SRCS= cub3d.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c srcs/parsing/utils_n01.c

NAME=game 

OBJS=$(SRCS:.c=.o)

all: $(NAME)


$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
 
clean:
	rm -rf 

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean 