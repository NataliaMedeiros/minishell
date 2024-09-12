/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:03:51 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/10 16:28:53 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define FD 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_adapted_atoi(const char *nptr);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(int fd, char *s);
int		ft_putnbr_nl(int nb);
int		ft_putnbr(int nb);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstr(char *str);
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strcharcat(char *dest, const char src);
char	*ft_strcharjoin(char *s1, char s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen_nl(const char *s);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
size_t	find_nl(char *text);
char	*ft_join_str(char *prev_line, char *text);
char	*ft_strtrim_beginning(char const *s1, char const *set);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr_arg(const char *s, int c);
long	ft_atoi_long(char *str, long nb);
int		ft_strchr_pos(const char *s, int c);

#endif
