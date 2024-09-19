/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:42:13 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/18 14:27:01 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	multiple_infile_cleaner(t_parser **parser, t_infile *temp)
{
	t_infile	*current;
	t_infile	*next;

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
	if (ft_strcmp(current->type, "heredoc") == 0)
		(*parser)->fd_infile = open(current->name, O_RDONLY, 0644);
}

void	exec_infile(t_parser **parser, t_data *data)
{
	t_infile	*temp;

	temp = (*parser)->infile;
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
	multiple_infile_cleaner(parser, temp);
}
