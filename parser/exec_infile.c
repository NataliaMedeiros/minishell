/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:42:13 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/30 14:42:24 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_infile(t_parser **parser, t_data *data)
{
	while ((*parser)->infile->next != NULL)
	{
		if (ft_strcmp((*parser)->infile->type, "infile") == 0)
		{
			(*parser)->fd_infile = open((*parser)->infile->name,
					O_RDONLY, 0644);
			minus_one_verificator(parser);
		}
		else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
			handle_heredoc(parser, data);
		(*parser)->infile = (*parser)->infile->next;
	}
	if (ft_strcmp((*parser)->infile->type, "infile") == 0)
	{
		(*parser)->fd_infile = open((*parser)->infile->name,
				O_RDONLY, 0644);
		minus_one_verificator(parser);
	}
	else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		handle_heredoc(parser, data);
}
