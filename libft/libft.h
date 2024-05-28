/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:03:51 by natalia       #+#    #+#                 */
/*   Updated: 2024/05/28 11:14:10 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int		ft_adapted_atoi(const char *nptr);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(int fd, char *s);
int		ft_putnbr_nl(int nb);
int		ft_putnbr(int nb);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstr(char *str);
char	*ft_strcat(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strcharcat(char *dest, const char src);
char	*ft_strcharjoin(char *s1, char s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen_nl(const char *s);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
size_t	find_nl(char *text);
char	*ft_join_str(char *prev_line, char *text);

#endif
