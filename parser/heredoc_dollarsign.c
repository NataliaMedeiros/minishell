/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dollarsign.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/18 17:11:31 by natalia       ########   odam.nl         */
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
	int		j;

	j = 0;
	while (data.envp[j])
	{
		if (ft_strncmp(data.envp[j], var, len) == 0)
		{
			return (ft_strdup(data.envp[j] + (len + 1)));
			break ;
		}
		j++;
	}
	return ("");
}

static char	*get_var(char *line, int start, t_data data)
{
	char	*var_name;
	char	*var_value;
	int		end;
	char	*new_line;

	end = var_end(line, start);
	var_name = ft_substr(line, start, start - end);
	var_value = search_envp(data, var_name, end - start);
	new_line = replace_var(line, var_value, start, end);
	return (new_line);
}

/* This function replaces the env variable to it's value and return the line
with ALL env variable replaced on the right place when we are working with
heredoc NOTE: On the subject is specified that the env variable just be
replaced ONLY when we have DOUBLE quotes or NO quotes (if we have single
quotes it should NOT be replaced)*/
char	*handle_dollar_sign(char *line, t_data data)
{
	int		i;
	char	*new_line;

	if (ft_strchr(line, '"') != NULL || ft_strchr(line, '\'') == NULL)
	{
		printf("hello\n");
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '$' && line[i + 1] != '"' && line [i + 1] != '\0')
			{
				new_line = get_var(line, i + 1, data);
				line = new_line;
				i += 2;
			}
			else if (line[i] == '$' && line [i + 1] == '\0')
			{
				new_line = line;
				break ;
			}
			i++;
		}
		if (new_line != NULL)
			return (new_line);
	}
	return (line);
}
