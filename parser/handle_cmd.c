/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:33:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/16 16:24:02 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	has_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

bool	has_flags(char *arg, t_parser **parser)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '-' && arg[i + 1] == 'n' && (arg[i + 2] == 'n'
				|| arg[i + 2] == ' ' || arg[i + 2] == '\0'))
		{
			(*parser)->flag = true;
			return (true);
		}
		else
			return (false);
		i++;
	}
	return (false);
}

static int	fill_echo_argument(t_parser **parser, t_data data, char *arg, int j)
{
	char	*temp;
	char	*new_cmd;

	if (ft_strchr(arg, '$') != NULL)
		temp = handle_dollar_sign(arg + j, data);
	else
		temp = ft_strdup(arg + j);
	if (temp == NULL)
		return (1);
	if (has_flags(temp, parser) == true)
		new_cmd = remove_flags(temp);
	else
		new_cmd = ft_strdup(temp);
	if (new_cmd == NULL)
		return (1);
	if (has_quotes(new_cmd) == true)
		(*parser)->cmd[1] = remove_quotes(new_cmd);
	else
		(*parser)->cmd[1] = ft_strdup(new_cmd);
	if ((*parser)->cmd[1] == NULL)
		return (free(temp), free(new_cmd), 1);
	return (free(new_cmd), free(temp), 0);
}

int	fill_echo_cmd(t_parser	**parser, t_data data, int i)
{
	char	*arg;
	int		len_arg;
	int		j;

	j = 0;
	arg = ft_strchr_arg(data.cmd_table[i], ' ');
	if (arg != NULL)
	{
		while (arg[j] == ' ')
			j++;
		len_arg = arg - data.cmd_table[i] - 1;
		(*parser)->cmd[0] = ft_calloc(len_arg + 2, sizeof(char));
		if ((*parser)->cmd[0] == NULL)
			return (1);
		ft_strlcpy((*parser)->cmd[0], data.cmd_table[i], len_arg + 1);
		if (fill_echo_argument(parser, data, arg, j) == 1)
			return (1);
	}
	else
		(*parser)->cmd[0] = ft_strdup(data.cmd_table[i]);
	return (0);
}
