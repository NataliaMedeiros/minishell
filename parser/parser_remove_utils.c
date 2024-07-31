/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:34:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/31 14:58:00 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_without_quotes(char *cmd, int i, char *new_cmd)
{
	int		j;
	bool	has_double_quotes;

	j = 0;
	has_double_quotes = false;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
			has_double_quotes = !has_double_quotes;
		if (cmd[i] == '$' && (cmd[i + 1] == '\''
				|| cmd[i + 1] == '"'))
			i++;
		if ((cmd[i] != '"' && cmd[i] != '\'')
			|| (cmd[i] == '\'' && has_double_quotes == true))
		{
			new_cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
}

char	*remove_quotes(char *cmd)
{
	char	*new_cmd;
	int		i;

	new_cmd = ft_calloc(sizeof(char), ft_strlen(cmd));
	if (new_cmd == NULL)
		return (NULL);
	i = 0;
	if (cmd[i] == '"' && cmd[i + 1] == '\0')
		return ("\0");
	fill_without_quotes(cmd, i, new_cmd);
	return (new_cmd);
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
