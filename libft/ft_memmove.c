/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 18:03:21 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:30:14 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*new_dest;
	unsigned const char	*new_src;

	i = 0;
	new_dest = (unsigned char *)dest;
	new_src = (unsigned const char *)src;
	if (new_dest > new_src)
	{
		i = n;
		while (i > 0)
		{
			new_dest[i - 1] = new_src[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
