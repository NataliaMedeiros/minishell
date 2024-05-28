/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 18:21:17 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:30:34 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*new_s;
	size_t			i;

	new_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		new_s[i] = c;
		i++;
	}
	return (s);
}
