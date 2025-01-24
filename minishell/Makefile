NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline

SRCS = srcs/split.c srcs/split_utils.c srcs/split_utils_utils.c srcs/command.c srcs/command2.c \
	   srcs/command_utils.c srcs/env.c srcs/env_utils.c srcs/exec.c srcs/exec_utils.c \
	   srcs/ft_heredoc.c srcs/chevron.c srcs/chevrons_other.c srcs/chevron_utils.c \
	   srcs/utils.c srcs/free.c srcs/main.c \
	   

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) -I. -I$(LIBFTDIR) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)
	@echo "Compiled $(NAME) successfully!"

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
