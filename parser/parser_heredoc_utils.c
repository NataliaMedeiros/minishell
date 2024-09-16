/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_heredoc_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/13 18:01:20 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/13 18:02:48 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_lim_quotes(char *limiter)
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
		if (limiter[i] != '"' && limiter[i] != '\'')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

static char	*remove_lim_backslash(char *limiter)
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
		if (limiter[i] != '\\')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

char	*find_limiter(t_parser **parser)
{
	char	*limiter;

	if (ft_strchr((*parser)->infile->name, '"') != NULL
		|| ft_strchr((*parser)->infile->name, '\'') != NULL)
		limiter = remove_lim_quotes((*parser)->infile->name);
	else if (ft_strchr((*parser)->infile->name, '\\') != NULL)
		limiter = remove_lim_backslash((*parser)->infile->name);
	else
		limiter = (*parser)->infile->name;
	return (limiter);
}
