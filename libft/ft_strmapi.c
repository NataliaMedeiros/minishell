/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 08:20:21 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:27:13 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s || !f)
	{
		return (NULL);
	}
	new_s = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_s == NULL)
	{
		return (NULL);
	}
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
