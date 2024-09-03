# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: natalia <natalia@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 16:50:00 by edribeir      #+#    #+#                  #
#    Updated: 2024/09/03 14:42:22 by natalia       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

LIBFTDIR = libft

CFLAGS = -Wall -Werror -Wextra -g -I/opt/hmomebrew/Cellar/readline/8.2.10/include
#CFLAGS += -fsanitize=address
LFLAGS = -L /opt/homebrew/Cellar/readline/8.2.10/lib -lreadline #MAC M1
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
		check_input.c \
		utils.c \
		parser/parser.c \
		parser/parser_heredoc.c \
		parser/parser_utils.c \
		parser/temporary_functions.c \
		parser/struct_utils.c \
		parser/handle_cmd.c \
		parser/parser_remove_utils.c \
		parser/handle_files.c \
		parser/handle_infile.c \
		parser/handle_outfile.c \
		parser/parser_env.c \
		parser/fill_parser.c \
		parser/parser_get_cmd.c \
		parser/exec_infile.c \
		expander/dollarsign.c \
		expander/dollarsign_utils.c \
		builtins/manager_builtin.c \
		builtins/echo_n.c \
		builtins/pwd.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/cd_utils.c \
		builtins/unset.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/exit.c \
		execute/execute_main.c \
		execute/execute_utils.c \
		execute/single_cmd.c \
		execute/multiple_cmd.c \
		signal/signal_handler.c \
		utils/error_utils.c \
		utils/exit_utils.c \
		utils/free_utils.c \

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
