NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline

SRCS = split.c split_utils.c split_utils_utils.c command.c command2.c \
	   command_utils.c env.c env_utils.c exec.c exec_utils.c \
	   ft_heredoc.c chevron.c chevrons_other.c chevron_utils.c \
	   utils.c main.c \
	   

LIBFTDIR = ../libft
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
