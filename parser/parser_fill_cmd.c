/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:33:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/15 16:03:41 by nmedeiro      ########   odam.nl         */
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

bool	has_flags(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '-')
		{
			if (arg[i + 1] == 'n' && (arg[i + 2] == 'n' || arg[i + 2] == ' '))
				return (true);
		}
		if (arg[i] == '"' || arg[i] == '\'')
			break ;
		i++;
	}
	return (false);
}

static int	fill_valid_echo(t_parser **parser, t_data data, int i)
{
	char	*temp;
	char	*arg;
	char	*new_cmd;
	int		j;
	int		len_arg;

	j = 0;
	arg = ft_strchr_adp(data.cmd_lst[i], ' ');
	len_arg = arg - data.cmd_lst[i];
	(*parser)->cmd[0] = ft_calloc(len_arg + 2, sizeof(char));
	if ((*parser)->cmd[0] == NULL)
		return (1);
	ft_strlcpy((*parser)->cmd[0], data.cmd_lst[i], len_arg + 1);
	temp = handle_dollar_sign(arg, data);
	if (temp == NULL)
		return (1);
	if (has_flags(temp) == true)
	{
		new_cmd = remove_flags(temp);
		(*parser)->flag = true;
	}
	else
		new_cmd = strdup(temp);
	if (has_quotes(new_cmd) == true)
		(*parser)->cmd[1] = remove_quotes(new_cmd);
	else
		(*parser)->cmd[1] = ft_strdup(new_cmd);
	if ((*parser)->cmd[1] == NULL)
		return (1);
	return (free(new_cmd), 0);
}

static int	fill_cmd_mode_echo(t_parser	**parser, t_data data, int i)
{
	(*parser)->cmd = ft_calloc(sizeof(char *), 3);
	if ((*parser)->cmd == NULL)
		return (1);
	if (fill_valid_echo(parser, data, i) == 1)
		return (1);
	return (0);
}

int	fill_cmd(t_parser **parser, t_data data, int i)
{
	if (ft_strncmp(data.cmd_lst[i], "echo", 4) == 0)
	{
		if (fill_cmd_mode_echo(parser, data, i) == 1)
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
