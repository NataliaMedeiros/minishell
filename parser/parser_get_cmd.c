/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_cmd.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:35:29 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/02 15:36:05 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_len(const char *s, int start, size_t len)
{
	if (ft_strlen(s) <= len)
		return (ft_strlen(s) - start);
	if (ft_strlen(s) == 1 || start >= (int)ft_strlen(s))
		return (0);
	else if (ft_strlen(s) - start < len)
		return (ft_strlen(s) - start);
	return (len);
}

static int	remove_space_at_begging(const char *s, int start)
{
	while (s[start] == ' ')
		start++;
	return (start);
}

static char	*write_substring(size_t len, int unsigned start,
	char const *s, bool has_double_quotes)
{
	size_t	i;
	char	*substring;

	i = 0;
	substring = ft_calloc(len + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		if (s[start] == '"')
			has_double_quotes = !has_double_quotes;
		if (return_substring(s, start,
				has_double_quotes) == true)
			return (substring);
		if (s[start] == ' ' && s[start + 1] == ' ')
			start++;
		else
		{
			substring[i] = s[start];
			i++;
			start++;
		}
	}
	return (substring);
}

char	*get_cmd(char const *s, int unsigned start, size_t len)
{
	char	*substring;
	bool	has_double_quotes;

	has_double_quotes = false;
	if (!s)
		return (NULL);
	start = remove_space_at_begging(s, start);
	len = check_len(s, start, len);
	substring = write_substring(len, start, s, has_double_quotes);
	return (substring);
}
