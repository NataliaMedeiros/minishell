/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_outfile.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 11:32:40 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/15 16:33:37 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int handle_redirection_out(t_data *data, int i)
{
	char **temp;

	temp = split_redirection_first(data->cmd_table[i + 1]);
	if (temp == NULL)
		return (1);
	if (temp[1] != NULL)
	{
		data->parser->cmd = ft_split(temp[1], ' ');
		if (data->parser->cmd == NULL)
			return (1);
	}
	data->parser->outfile = ft_strdup(temp[0]);
	if (data->parser->outfile == NULL)
		return (1);
	return (0);
}
int	handle_outfile(t_data *data, int i, bool start_with_redirection)
{
	if (start_with_redirection == true)
	{
		if (handle_redirection_out(data, i) == 1)
			return (1);
	}
	else
	{
		data->parser->outfile = ft_strdup(data->cmd_table[i + 1]);
		if (data->parser->outfile == NULL)
			return (1);
	}
	if (data->cmd_table[i][1] == '>')
		data->parser->fd_outfile = open(data->parser->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		data->parser->fd_outfile = open(data->parser->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->parser->fd_outfile == -1)
		return (error_msg("Failure to open outfile\n"),
			free(data->parser->outfile), 1);
	return (0);
}
