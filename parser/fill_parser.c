/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/29 16:36:53 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/18 14:07:04 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipe(t_parser **parser, bool *has_pipe)
{
	(*parser)->pipe = new_struct();
	if ((*parser)->pipe == NULL)
		return (error_msg("Failed to allocate memory for pipe\n"), 1);
	*has_pipe = true;
	(*parser) = (*parser)->pipe;
	return (0);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "''") == 0 || ft_strcmp(str, """") == 0)
		return (true);
	if (str[i] == '\'' || str[i] == '"')
	{
		i++;
		while (str[i] != '\0')
		{
			while (str[i] == ' ')
				i++;
			if ((str[i] == '\'' || str[i] == '"') && str[i + 1] == '\0')
				return (true);
			if (str[i] != ' ')
				return (false);
			i++;
		}
	}
	return (false);
}

char	*get_temp(t_data data, int i)
{
	char	*temp;
	char	*cmd;

	if (ft_strchr(data.cmd_table[i], '$') != NULL)
		temp = handle_dollar_sign(data.cmd_table[i], data);
	else
		temp = ft_strdup(data.cmd_table[i]);
	if (check_quotes(temp) == true)
		return (temp);
	if (has_quotes(temp) == true)
		cmd = remove_quotes(temp);
	else
		cmd = ft_strdup(temp);
	free(temp);
	return (cmd);
}

int	fill_cmd(t_parser **parser, t_data data, int i, bool *has_pipe)
{
	char	*temp;

	if (ft_strncmp(data.cmd_table[i], "echo", 4) == 0)
	{
		(*parser)->cmd = ft_calloc(sizeof(char *), 3);
		if ((*parser)->cmd == NULL)
			return (1);
		if (fill_echo_cmd(parser, data, i) == 1)
			return (1);
	}
	else
	{
		temp = get_temp(data, i);
		(*parser)->cmd = ft_split(temp, ' ');
		if ((*parser)->cmd == NULL)
			return (1);
		free (temp);
	}
	*has_pipe = false;
	return (0);
}

int	fill_parser(t_data	data, t_parser	**parser)
{
	int		i;
	bool	has_pipe;

	i = 0;
	has_pipe = false;
	while (data.cmd_table[i] != NULL)
	{
		if (data.cmd_table[i][0] == '|')
		{
			if (handle_pipe(parser, &has_pipe) != 0)
				return (error_msg("failure on handle pipe"), 1);
		}
		else if (data.cmd_table[i][0] == '>' || data.cmd_table[i][0] == '<')
		{
			if (handle_files(data, parser, i, &has_pipe) != 0)
				return (1);
			i++;
		}
		else
			if (fill_cmd(parser, data, i, &has_pipe) != 0)
				return (error_msg("failure on fill cmd"), 1);
		i++;
	}
	return (0);
}
