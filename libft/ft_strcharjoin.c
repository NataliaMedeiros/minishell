/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcharjoin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/30 17:29:09 by natalia       #+#    #+#                 */
/*   Updated: 2024/05/07 13:27:53 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcharjoin(char *s1, char s2)
{
	char	*s;
	size_t	len;

	len = 3;
	if (s1 != NULL)
		len += ft_strlen(s1);
	s = ft_calloc(sizeof(char), len);
	if (s == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strcat(s, s1);
	ft_strcharcat(s, s2);
	return (s);
}
