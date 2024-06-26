/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_adapted_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 08:19:25 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/06/17 12:43:58 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator_adp(char c, char const *separators)
{
	for (int i = 0; i < 5; i++)
	{
		if (c == separators[i])
			return (1);
	}
	return (0);
}

int	count_words_adp(char const *s, char const *separators)
{
	int		i;
	int		i_word;

	i = 0;
	i_word = 0;
	while (s[i] != '\0')
	{
		while (is_separator_adp(s[i], separators))
			i++;
		if (s[i])
			i_word++;
		while (!is_separator_adp(s[i], separators) && s[i] != '\0')
			i++;
	}
	return (i_word);
}

char	*malloc_str_adp(char const *s, char const *separators)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && !is_separator_adp(s[i], separators))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] && !is_separator_adp(s[i], separators))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**free_words_adp(char **new_word, int i)
{
	while (i >= 0)
	{
		free (new_word[i]);
		i--;
	}
	free (new_word);
	return (new_word);
}

char	**filling_new_word_adp(char **new_word, const char *s, char const *separators, int i)
{
	while (*s != '\0')
	{
		while (*s && is_separator_adp(*s, separators))
			s++;
		if (*s && !is_separator_adp(*s, separators))
		{
			new_word[i] = malloc_str_adp(s, separators);
			if (new_word[i] == NULL)
			{
				free_words_adp(new_word, i);
				return (NULL);
			}
			i++;
			while (*s && !is_separator_adp(*s, separators))
				s++;
		}
	}
	new_word[i] = NULL;
	return (new_word);
}

char	**ft_split_adp(char const *s, char const *separators)
{
	char	**new_word;
	int		i;

	if (!s || !separators)
		return (NULL);
	new_word = (char **)malloc((count_words_adp(s, separators) + 1) * sizeof(char *));
	if (!new_word)
		return (NULL);
	i = 0;
	new_word = filling_new_word_adp(new_word, s, separators, i);
	return (new_word);
}
