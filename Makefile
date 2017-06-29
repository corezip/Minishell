
NAME	= minishell

SRC		=	cd_command.c echo.c env.c execve.c helper.c main.c \
ft_split_whitespaces.c cd.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(OBJ) -o $(NAME) -L libft/ -lft
	@echo "\033[32mMinishell: Built ft_ls. ~(˘▾˘~) \033[0m"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)
	@echo "\033[32mMinishell: Cleaned up object files. ~(˘▾˘~) \033[0m"

fclean: clean
	@$(MAKE) -C ./libft/ fclean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)