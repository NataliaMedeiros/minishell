/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 18:03:13 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:28:56 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	i = 0;
	new_s1 = (unsigned char *)s1;
	new_s2 = (unsigned char *)s2;
	while (i < (int)n)
	{
		if (new_s1[i] == new_s2[i])
			i++;
		else
			return (new_s1[i] - new_s2[i]);
	}
	return (0);
}
