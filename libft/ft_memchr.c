/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 18:03:09 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:28:36 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_s;

	i = 0;
	new_s = (unsigned char *)s;
	while (i < n)
	{
		if (new_s[i] == (unsigned char)c)
			return (new_s + i);
		i++;
	}
	return (NULL);
}
