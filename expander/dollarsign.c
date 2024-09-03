/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/03 14:14:01 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*replace_dollar_sign(char *line, char *new_line, t_data data)
{
	int		i;
	bool	has_single_quote;
	bool	has_double_quotes;

	i = 0;
	has_single_quote = false;
	has_double_quotes = false;
	while (line[i])
	{
		if (line[i] == '\'')
			has_single_quote = !has_single_quote;
		if (line[i] == '"')
			has_double_quotes = !has_double_quotes;
		if (line[i] == '$' && line[i + 1] != '"' && line[i + 1] != '\0'
			&& line[i + 1] != ' ' && line[i + 1] != '?'
			&& ((!has_double_quotes && !has_single_quote) || has_double_quotes))
		{
			new_line = get_var(line, i + 1, data);
			line = new_line;
			if (ft_strcmp(new_line, "") == 0 || ft_strlen(new_line) <= 3)
				return (new_line);
		}
		else if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == '"'))
		{
			new_line = line;
			break ;
		}
		i++;
	}
	return (new_line);
}

/* This function replaces the env variable to it's value and return the line
with ALL env variable replaced on the right place when we are working with
heredoc NOTE: On the subject is specified that the env variable just be
replaced ONLY when we have DOUBLE quotes or NO quotes (if we have single
quotes it should NOT be replaced)*/
char	*handle_dollar_sign(char *line, t_data data)
{
	char	*new_line;

	printf("%s\n", line);
	new_line = NULL;
	if (ft_strchr(line, '"') != NULL || ft_strchr(line, '\'') == NULL)
	{
		new_line = replace_dollar_sign(line, new_line, data);
		if (new_line != NULL)
			return (new_line);
	}
	return (line);
}
