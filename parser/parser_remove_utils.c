/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:34:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/17 13:57:02 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *limiter)
{
	char	*new_limiter;
	int		i;
	int		j;

	new_limiter = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (new_limiter == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (limiter[i] != '\0')
	{
		if ((limiter[i] == '$' && limiter[i + 1] == '"')
			|| (limiter[i] == '$' && limiter[i + 1] == '\''))
			i++;
		if (limiter[i] != '"' && limiter[i] != '\'')
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
		if (i < len && (arg[i] == '-' && arg[i + 1] == 'n')) //maybe while
		{
			prev_i = i;
			i++;
			while (arg[i] == 'n')
				i++;
			if (arg[i] != ' ')
			{
				i = prev_i;
				break ;
			}
		}
		else
			break;
		i++;
		// if (arg[i] == ' ')
		// 	i++;
		// else
		// 	i = prev_i;
	}
	new_len = len - i + 1;
	new_arg = (char *)malloc(sizeof(char) * new_len);
	if (new_arg == NULL)
		return (NULL);
	ft_strlcpy(new_arg, arg + i, new_len);
	return (new_arg);
}
