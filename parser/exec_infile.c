/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:42:13 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/09 15:20:51 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	exec_infile(t_parser **parser, t_data *data)
{
	t_infile	*temp = (*parser)->infile;
	t_infile	*current;
	t_infile	*next;

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
	current = temp;
	while (current->next != NULL)
	{
		next = current->next;
		if (ft_strcmp(current->type, "heredoc") == 0)
			unlink(current->name);
		free(current->name);
		free(current);
		current = next;
	}
}
