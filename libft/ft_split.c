/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 08:19:25 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:28:11 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int		i;
	int		i_word;

	i = 0;
	i_word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			i_word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (i_word);
}

char	*malloc_str(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**free_words(char **new_word, int i)
{
	while (i >= 0)
	{
		free (new_word[i]);
		i--;
	}
	free (new_word);
	return (new_word);
}

char	**filling_new_word(char **new_word, const char *s, char c, int i)
{
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			new_word[i] = malloc_str(s, c);
			if (new_word[i] == NULL)
			{
				free_words(new_word, i);
				return (NULL);
			}
			i++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	new_word[i] = NULL;
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	char	**new_word;
	int		i;

	if (!s)
		return (NULL);
	new_word = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!new_word)
		return (NULL);
	i = 0;
	new_word = filling_new_word(new_word, s, c, i);
	return (new_word);
}
