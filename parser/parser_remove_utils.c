/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:34:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/13 17:17:19 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_without_quotes(char *arg, char *new_arg)
{
	int		j;
	int		i;
	bool	dbl_q;
	bool	sgl_q;

	j = 0;
	i = 0;
	dbl_q = false;
	sgl_q = false;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' && !sgl_q)
			dbl_q = !dbl_q;
		else if (arg[i] == '\'' && !dbl_q)
			sgl_q = !sgl_q;
		if (arg[i] == '$' && (arg[i + 1] == '\'' || arg[i + 1] == '"'))
			i++;
		if ((arg[i] != '"' && arg[i] != '\'')
			|| (arg[i] == '\'' && dbl_q == true) || (arg[i] == '"' && sgl_q))
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
