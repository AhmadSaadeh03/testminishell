CC = cc 

CFLAGS = -Wall -Wextra -Werror -g

SRCS =  srcs/main.c srcs/tokeniz/split.c srcs/error_handling/checks.c srcs/initilize.c srcs/parse/parse.c srcs/parse/fill_cmd.c srcs/error_handling/ft_free.c srcs/expand/expand.c \
	srcs/tokeniz/helpers.c srcs/error_handling/handle_error.c srcs/expand/handle_env.c srcs/parse/handle_redirction.c srcs/expand/handle_export.c \
	srcs/execute/execute_builtin.c srcs/execute/external_cmd.c srcs/expand/expand_helpers.c srcs/error_handling/extra_free.c srcs/tokeniz/split_helper.c \
	srcs/execute/builtin_fun/ft_echo.c srcs/execute/builtin_fun/ft_export.c srcs/execute/builtin_fun/ft_exit.c
OBJ = $(SRCS:.c=.o)

LIBFT_DIR = libft


LIBFT_A = libft/libft.a

NAME = minishell



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
