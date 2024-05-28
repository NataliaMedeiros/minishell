/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 18:21:23 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:12:44 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_s;

	new_s = malloc(ft_strlen(s) + 1);
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s, ft_strlen(s) + 1);
	return (new_s);
}
