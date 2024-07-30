/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:34:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/30 14:20:27 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *limiter)
{
	char	*new_limiter;
	bool	has_double_quotes;
	int		i;
	int		j;

	new_limiter = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (new_limiter == NULL)
		return (NULL);
	i = 0;
	j = 0;
	has_double_quotes = false;
	if (limiter[i] == '"' && limiter[i + 1] == '\0')
		return ("\0");
	while (limiter[i] != '\0')
	{
		if (limiter[i] == '"')
			has_double_quotes = !has_double_quotes;
		if (limiter[i] == '$' && limiter[i + 1] == '\'')
			i++;
		if ((limiter[i] != '"' && limiter[i] != '\'')
			|| (limiter[i] == '\'' && has_double_quotes == true))
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

char	*remove_flags(char *arg)
{
	char	*new_arg;
	int		i;
	int		len;
	int		new_len;
	int		prev_i;

	i = 0;
	len = ft_strlen(arg);
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
	new_len = len - i + 1;
	new_arg = (char *)malloc(sizeof(char) * new_len);
	if (new_arg == NULL)
		return (NULL);
	ft_strlcpy(new_arg, arg + i, new_len);
	return (new_arg);
}
