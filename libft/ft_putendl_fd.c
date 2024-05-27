/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:16:35 by natalia       #+#    #+#                 */
/*   Updated: 2024/04/09 11:19:32 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(int fd, char *s)
{
	int	len;

	len = ft_strlen(s);
	write (fd, s, len);
	write(fd, "\n", 1);
}
