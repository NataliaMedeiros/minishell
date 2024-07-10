/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_adapted.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:37:13 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/10 20:37:14 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_adapted(char const *s1, char const *set)
{
	char	*new_s1;
	int		start;
	int		end;
	int		new_len;

	start = 0;
	end = ft_strlen(s1) -1;
	while ((s1[start] != '\0' && s1[start] == set[start])
		|| s1[start] == ' ')
		start++;
	new_len = end - start + 2;
	new_s1 = (char *)malloc(sizeof(char) * new_len);
	if (new_s1 == NULL)
		return (NULL);
	ft_strlcpy(new_s1, s1 + start, new_len);
	return (new_s1);
}