/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:33:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/16 14:28:18 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	has_quotes(char *arg)
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

bool	has_flags(char *arg, t_parser	**parser)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '-')
		{
			if (arg[i + 1] == 'n' && (arg[i + 2] == 'n' || arg[i + 2] == ' '))
			{
				(*parser)->flag = true;
				return (true);
			}
		}
		if (arg[i] == '"' || arg[i] == '\'')
			break ;
		i++;
	}
	return (false);
}

static int	fill_echo_argument(t_parser **parser, t_data data, char *arg, int j)
{
	char	*temp;
	char	*new_cmd;

	if (ft_strchr(arg, '$') != NULL)
	{
		temp = handle_dollar_sign(arg + j, data);
		if (temp == NULL)
			return (1);
	}
	else
		temp = arg + j;
	if (has_flags(temp, parser) == true)
		new_cmd = remove_flags(temp);
	else
		new_cmd = temp;
	if (has_quotes(new_cmd) == true)
		(*parser)->cmd[1] = remove_quotes(new_cmd);
	else
		(*parser)->cmd[1] = ft_strdup(new_cmd);
	if ((*parser)->cmd[1] == NULL)
		return (1);
	return (0);
}

static int	fill_echo_cmd(t_parser	**parser, t_data data, int i)
{
	char	*arg;
	int		len_arg;
	int		j;

	j = 0;
	arg = ft_strchr_adp(data.cmd_lst[i], ' ');
	while (arg[j] == ' ')
		j++;
	len_arg = arg - data.cmd_lst[i];
	(*parser)->cmd[0] = ft_calloc(len_arg + 2, sizeof(char));
	if ((*parser)->cmd[0] == NULL)
		return (1);
	ft_strlcpy((*parser)->cmd[0], data.cmd_lst[i], len_arg + 1);
	if (fill_echo_argument(parser, data, arg, j) == 1)
		return (1);
	return (0);
}

int	fill_cmd(t_parser **parser, t_data data, int i)
{
	if (ft_strncmp(data.cmd_lst[i], "echo", 4) == 0)
	{
		(*parser)->cmd = ft_calloc(sizeof(char *), 3);
		if ((*parser)->cmd == NULL)
			return (1);
		if (fill_echo_cmd(parser, data, i) == 1)
			return (error_msg("Failure to fill cmd\n"), 1);
		printf("flag %d\n", (*parser)->flag);
	}
	else
		(*parser)->cmd = ft_split(data.cmd_lst[i], ' ');
	if ((*parser)->cmd == NULL)
		return (error_msg("Failure to fill cmd\n"), 1);
	return (0);
}

// TODO
//echo             eduarda
// echoooooooo eduarda
// echo-nnnnnn edu
// echo -nnnnnn -n -n -nnnnn edu
//colocar espaco depois do heredoc prompt
