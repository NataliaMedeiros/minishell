/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/30 16:19:06 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*replace_var(char *line, char *var_exp, int start, int end)
{
	char	*first_part;
	char	*last_part;
	char	*temp;
	char	*new_line;

	first_part = ft_substr(line, 0, start - 1);
	temp = ft_strjoin(first_part, var_exp);
	last_part = ft_substr(line, end, ft_strlen(line));
	new_line = ft_strjoin(temp, last_part);
	free(first_part);
	free(temp);
	free(last_part);
	return (new_line);
}

static int	var_end(char *line, int i)
{
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		i++;
		if (line[i] == ' ')
			break ;
	}
	return (i);
}

static char	*search_envp(t_data data, char *var, int len)
{
	char *temp;

	temp = ft_strjoin(var, "=");
	while (data.env)
	{
		if (ft_strncmp(data.env->key_word, temp, len + 1) == 0)
		{
			return (free(temp), ft_strdup(data.env->info));
		}
		data.env = data.env->next;
	}
	return (free(temp), "");
}

static char	*get_var(char *line, int start, t_data data)
{
	char	*var_name;
	char	*var_value;
	int		end;
	char	*new_line;

	end = var_end(line, start);
	var_name = ft_substr(line, start, end - start);
	var_value = search_envp(data, var_name, end - start);
	new_line = replace_var(line, var_value, start, end);
	return (new_line);
}

char	*replace_dollar_sign(char *line, char *new_line, t_data data)
{
	int i;
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
		if (line[i] == '$' && line[i + 1] != '"' && line [i + 1] != '\0'
				&& line[i + 1] != ' ' && line[i + 1] != '?'
				&& ((!has_double_quotes && !has_single_quote) || has_double_quotes))
		{
			new_line = get_var(line, i + 1, data);
			line = new_line;
			if (strcmp(new_line, "") == 0 || ft_strlen(new_line) <= 3)
				return (new_line);
		}
		else if (line[i] == '$' && (line [i + 1] == '\0' || line [i + 1] == '"'))
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
