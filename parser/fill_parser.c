/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/29 16:36:53 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/29 16:37:23 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipe(t_parser **parser)
{
	(*parser)->pipe = new_struct();
	if ((*parser)->pipe == NULL)
		return (error_msg("Failed to allocate memory for pipe\n"), 1);
	(*parser) = (*parser)->pipe;
	return (0);
}

int	fill_parser(t_data	data, t_parser	**parser)
{
	int		i;
	bool	has_pipe;
	bool	start_with_redirection;

	i = 0;
	has_pipe = false;
	while (data.cmd_table[i] != NULL)
	{
		start_with_redirection = false;
		if (data.cmd_table[i][0] == '|')
		{
			if (handle_pipe(parser) != 0)
				return (error_msg("failure on handle pipe"), 1);
			has_pipe = true;
		}
		else if (data.cmd_table[i][0] == '>' || data.cmd_table[i][0] == '<')
		{
			if (i == 0)
				start_with_redirection = true;
			else if (has_pipe == true)
				start_with_redirection = true;
			if (handle_files(data, parser, i, start_with_redirection) != 0)
				return (error_msg("failure on handle files"), 1);
			i++;
			has_pipe = false;
		}
		else
		{
			if (fill_cmd(parser, data, i) != 0)
				return (error_msg("failure on fill cmd"), 1);
			has_pipe = false;
		}
		i++;
	}
	return (0);
}
