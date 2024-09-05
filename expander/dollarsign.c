/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/04 14:19:01 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_single_quote(char *line, int i, bool has_single_quote)
{
	if (line[i] == '\'')
		has_single_quote = !has_single_quote;
	return (has_single_quote);
}

bool	check_double_quote(char *line, int i, bool has_double_quote)
{
	if (line[i] == '"')
		has_double_quote = !has_double_quote;
	return (has_double_quote);
}

char	*replace_dollar_sign(char *l, char *new_line, t_data data)
{
	int		i;
	bool	sing_quote;
	bool	doub_quote;

	i = 0;
	sing_quote = false;
	doub_quote = false;
	while (l[i])
	{
		sing_quote = check_single_quote(l, i, sing_quote);
		doub_quote = check_double_quote(l, i, doub_quote);
		if (l[i] == '$' && l[i + 1] != '"' && l[i + 1] != '\0'
			&& l[i + 1] != ' ' && l[i + 1] != '?' && (ft_isalpha(l[i + 1]))
			&& ((!doub_quote && !sing_quote) || doub_quote))
		{
			new_line = get_var(l, i + 1, data);
			l = new_line;
			if (!*new_line || ft_strlen(new_line) <= 3)
				return (new_line);
		}
		else if (l[i] == '$' && (l[i + 1] == '\0' || l[i + 1] == '"'))
			new_line = ft_strdup(l);
		i++;
	}
	return (new_line);
}

char	*handle_dollar_sign(char *line, t_data data)
{
	char	*new_line;

	new_line = NULL;
	if (ft_strchr(line, '"') != NULL || ft_strchr(line, '\'') == NULL)
	{
		new_line = replace_dollar_sign(line, new_line, data);
		if (new_line != NULL)
			return (new_line);
	}
	return (ft_strdup(line));
}
