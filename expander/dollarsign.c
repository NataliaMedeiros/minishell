/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/04 12:09:32 by nmedeiro      ########   odam.nl         */
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
	char	*temp;

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

char	*get_var(char *line, int start, t_data data)
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

void	get_new_line(char **new_line, char **line, int i, t_data data)
{
	*new_line = get_var(*line, i + 1, data);
	*line = *new_line;
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
			get_new_line(&new_line, &l, i, data);
			if (!*new_line || ft_strlen(new_line) <= 3)
				return (new_line);
		}
		else if (l[i] == '$' && (l[i + 1] == '\0' || l[i + 1] == '"'))
			new_line = l;
		i++;
	}
	return (new_line);
}

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
