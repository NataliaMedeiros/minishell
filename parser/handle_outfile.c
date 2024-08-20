/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_outfile.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 11:32:40 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/20 13:56:09 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int handle_redirection_out(t_data data, t_parser **parser, int i)
{
	char **temp;

	temp = split_redirection_first(data.cmd_table[i + 1]);
	if (temp == NULL)
		return (1);
	if (temp[1] != NULL)
	{
		(*parser)->cmd = ft_split(temp[1], ' ');
		if ((*parser)->cmd == NULL)
			return (free_array(0, temp), 1);
	}
	(*parser)->outfile = ft_strdup(temp[0]);
	if ((*parser)->outfile == NULL)
		return (free_array(0, temp), 1);
	return (free_array(0, temp), 0);
}

int	handle_outfile(t_data data, t_parser **parser, int i, bool start_with_redirection)
{
	if (start_with_redirection == true)
	{
		if (handle_redirection_out(data, parser, i) == 1)
			return (error_msg("error on handle redirection out"), 1);
	}
	else
	{
		(*parser)->outfile = ft_strdup(data.cmd_table[i + 1]);
		if ((*parser)->outfile == NULL)
			return (error_msg("fail on dup outfile"), 1);
	}
	if (data.cmd_table[i][1] == '>')
		(*parser)->fd_outfile = open((*parser)->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		(*parser)->fd_outfile = open((*parser)->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*parser)->fd_outfile == -1)
		return (error_msg("Failure to open outfile\n"),
			free((*parser)->outfile), 1);
	return (0);
}
