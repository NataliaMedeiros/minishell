/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:33:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/15 11:51:48 by nmedeiro      ########   odam.nl         */
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
	char	*new_cmd;

	(*parser)->cmd[0] = ft_strdup("echo");
	if ((*parser)->cmd[0] == NULL)
		return (1);
	temp = handle_dollar_sign(
			ft_strtrim_adapted(data.cmd_lst[i], "echo "), data);
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
	return (free(temp), free(new_cmd), 0);
}

static int	fill_cmd_mode_echo(t_parser	**parser, t_data data, int i)
{
	if (ft_strncmp(data.cmd_lst[i], "echo", 4) == 0)
	{
		(*parser)->cmd = ft_calloc(sizeof(char *), 3);
		if ((*parser)->cmd == NULL)
			return (1);
		if (fill_valid_echo(parser, data, i) == 1)
			return (1);
	}
	else
	{
		(*parser)->cmd = ft_calloc(sizeof(char *), 2);
		if ((*parser)->cmd == NULL)
			return (1);
		(*parser)->cmd[0] = ft_strdup(data.cmd_lst[i]);
		error_msg("Invalid command\n");
	}
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
