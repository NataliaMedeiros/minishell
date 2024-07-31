# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: natalia <natalia@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 16:50:00 by edribeir      #+#    #+#                  #
#    Updated: 2024/07/31 14:07:57 by nmedeiro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

LIBFTDIR = libft

CFLAGS = -Wall -Werror -Wextra -g
CFLAGS += -fsanitize=address
LFLAGS = -L /opt/homebrew/Cellar/readline/8.2.1/lib -lreadline #MAC M1
#LFLAGS = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline #MAC based intel
#LFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline #linux
#LFLAGS = -lreadline

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
		free_utils.c \
		utils.c \
		parser/parser.c \
		parser/parser_heredoc.c \
		parser/parser_utils.c \
		parser/temporary_functions.c \
		parser/struct_utils.c \
		parser/parser_fill_cmd.c \
		parser/parser_remove_utils.c \
		parser/handle_files.c \
		parser/parser_env.c \
		expander/dollarsign.c \
		builtins/manager_builtin.c \
		builtins/echo_n.c \
		builtins/pwd.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/unset.c

OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFTDIR)
	@echo "Compiled ✅ $(LIBFT)"

$(NAME): $(LIBFT) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(BOLD)\n--------------------------------------$(RESET)"
	@echo "$(PINK)$(BOLD)\n\t Minishell ready! $(RESET)🎉\n"
	@echo "$(GREEN)$(BOLD)--------------------------------------\n$(RESET)"

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJECTS)
	@echo "$(GREEN)$(BOLD)\t OFILES Cleansed! $(RESET)🆗"

fclean:
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(OBJECTS)
	@echo "$(GREEN)$(BOLD)\t ALL Cleansed! $(RESET)🆗"

re: fclean all

PHONY: all clean fclean re
