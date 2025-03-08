CC = cc 

CFLAGS = -Wall -Wextra -Werror -g

<<<<<<< HEAD
SRCS = srcs/main.c srcs/split.c srcs/checks.c srcs/initilize.c
=======
<<<<<<< HEAD
SRCS = srcs/main.c srcs/split.c srcs/checks.c srcs/initilize.c srcs/parse.c
=======
SRCS = srcs/main.c srcs/split.c srcs/checks.c srcs/initilize.c srcs/parse.c srcs/ft_free.c
>>>>>>> f26bb66 (new)
>>>>>>> 5213311 (new)

OBJ = $(SRCS:.c=.o)

LIBFT_DIR = libft


LIBFT_A = libft/libft.a

NAME = Minishell



all:$(LIBFT_A) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft -lreadline -o $@

$(LIBFT_A) : 
	make -C $(LIBFT_DIR)
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean : clean
	$(MAKE) fclean -C  $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
