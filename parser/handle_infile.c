/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_infile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 11:27:24 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/09 12:20:38 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_infile	*new_infile(char *name, char *type)
{
	t_infile	*new_element;

	new_element = malloc(sizeof(t_infile));
	if (new_element == NULL)
		return (NULL);
	new_element->name = ft_strdup(name);
	new_element->type = type;
	new_element->next = NULL;
	return (new_element);
}

static void	add_infile_back(t_infile **head, char *name, char *type)
{
	t_infile	*current_node;
	t_infile	*new_node;

	current_node = *head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	new_node = new_infile(name, type);
	current_node->next = new_node;
}

static t_infile	*handle_redirection_in(t_data data, t_parser **parser, int i,
	char *type)
{
	char	**temp;

	temp = split_redirection_first(data.cmd_table[i + 1]);
	i = 0;
	if (temp[1] != NULL)
	{
		(*parser)->cmd = ft_split(temp[1], ' ');
		if ((*parser)->cmd == NULL)
			return (NULL);
	}
	if ((*parser)->infile == NULL)
		(*parser)->infile = new_infile(temp[0], type);
	else
		add_infile_back(&(*parser)->infile, temp[0], type);
	free(temp);
	return ((*parser)->infile);
}

int	handle_infile(t_data data, t_parser **parser, int i, bool start_redirection)
{
	char	*type;

	if (data.cmd_table[i][1] == '<')
		type = "heredoc";
	else
		type = "infile";
	if (start_redirection == true)
	{
		(*parser)->infile = handle_redirection_in(data, parser, i, type);
		if ((*parser)->infile == NULL)
			return (error_msg("failure on redirection in"), 1);
	}
	else
	{
		if ((*parser)->infile == NULL)
			(*parser)->infile = new_infile(data.cmd_table[i + 1], type);
		else
			add_infile_back(&(*parser)->infile, data.cmd_table[i + 1], type);
	}
	return (0);
}
