/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 12:57:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/04 12:51:04 by nmedeiro      ########   odam.nl         */
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
	free (var_name);
	free(var_value);
	return (new_line);
}

// void	get_new_line(char **new_line, char **line, int i, t_data data)
// {
// 	*new_line = get_var(*line, i + 1, data);
// 	*line = *new_line;
// }
