# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: natalia <natalia@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 16:50:00 by edribeir      #+#    #+#                  #
#    Updated: 2024/05/31 10:21:07 by natalia       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

RED = \033[31m
PINK = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[96m
CYAN = \033[36m
BOLD = \033[1m
RESET = \033[0m
# https://ss64.com/nt/syntax-ansi.html site that have colors

SOURCE = main.c \
		parser.c \

OBJECTS = $(SOURCE:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -L /opt/homebrew/Cellar/readline/8.2.1/lib -lreadline #MAC M1
#LFLAGS = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline #MAC based intel
#LFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline #linux
#LFLAGS = -lreadline

LIBFTDIR = libft

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFTDIR)
	@echo "Compiled ✅ $(LIBFT)"

$(NAME): $(LIBFT) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LFLAGS) $(LIBFT) -o $(NAME)
# @echo "$(PINK)$(BOLD)\n\t Ready! $(RESET)🎉\n" we can decide the colors together

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJECTS)
# @echo "$(GREEN)\t OFILES Cleansed! $(RESET)🆗"

fclean:
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(OBJECTS)
# @echo "$(GREEN)$(BOLD)\t ALL Cleansed! $(RESET)🆗"

re: fclean all

PHONY: all clean fclean re
