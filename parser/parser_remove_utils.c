/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:34:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/12 10:54:49 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_without_quotes(char *arg, char *new_arg)
{
	int		j;
	int		i;
	bool	has_double_quotes;
	bool	has_single_quotes;

	j = 0;
	i = 0;
	has_double_quotes = false;
	has_single_quotes = false;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' && !has_single_quotes)
			has_double_quotes = !has_double_quotes;
		else if (arg[i] == '\'' && !has_double_quotes)
			has_single_quotes = !has_single_quotes;
		if (arg[i] == '$' && (arg[i + 1] == '\''
				|| arg[i + 1] == '"'))
			i++;
		if ((arg[i] != '"' && arg[i] != '\'')
			|| (arg[i] == '\'' && has_double_quotes == true)
			||(arg[i] == '"' && has_single_quotes))
		{
			new_arg[j] = arg[i];
			j++;
		}
		i++;
	}
}

char	*remove_quotes(char *arg)
{
	char	*new_arg;

	new_arg = ft_calloc(sizeof(char), ft_strlen(arg));
	if (new_arg == NULL)
		return (NULL);
	if (arg[0] == '"' && arg[1] == '\0')
		return ("\0");
	fill_without_quotes(arg, new_arg);
	return (new_arg);
}

static int	count_flags(char *arg, int len)
{
	int		i;
	int		prev_i;

	i = 0;
	while (arg[i] != '\0' && (arg[i] == '-' || arg[i] == 'n' || arg[i] == ' '))
	{
		if (i < len && (arg[i] == '-' && arg[i + 1] == 'n'))
		{
			prev_i = i;
			i++;
			while (arg[i] == 'n')
				i++;
			if (arg[i] != ' ' && arg[i] != '\0')
			{
				i = prev_i;
				break ;
			}
			else if (arg[i] == '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

char	*remove_flags(char *arg)
{
	char	*new_arg;
	int		total_flags;
	int		len;
	int		new_len;

	len = ft_strlen(arg);
	total_flags = count_flags(arg, len);
	new_len = len - total_flags + 1;
	new_arg = ft_calloc(sizeof(char), new_len);
	if (new_arg == NULL)
		return (NULL);
	ft_strlcpy(new_arg, arg + total_flags, new_len);
	return (new_arg);
}
