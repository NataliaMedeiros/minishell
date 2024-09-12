NAME = libft.a

FILES =	ft_adapted_atoi.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_strcat.c \
		ft_strcharcat.c \
		ft_strcharjoin.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_strlen_nl.c \
		get_next_line_utils.c \
		get_next_line.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_split.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putnbr_fd.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strtrim_beginning.c \
		ft_atoi_long.c \
		ft_strchar_pos.c \

OFILES = $(FILES:%.c=%.o)

CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OFILES)
	@ar -rc $(NAME) $(OFILES)
	@echo "Compiled ✅ $^"

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)
	@echo
	@echo "Cleaned my_library ✅"

re: fclean all

.PHONY: all, clean, fclean, re
