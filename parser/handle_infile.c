/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_infile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 11:27:24 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/15 11:56:14 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_infile	*new_infile(char *name, char *type)
{
	t_infile	*new_element;

	new_element = malloc(sizeof(t_infile));
	if (new_element == NULL)
		return (NULL);
	new_element->name = name;
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
static int	handle_redirection_in(t_data	*data, int i, char *type)
{
	char		**new_cmd;

	new_cmd = split_redirection_first(data->cmd_table[i + 1]);
	i = 0;
	printf("%s\n", new_cmd[2]);
	if (new_cmd[1] != NULL)
		data->parser->cmd = ft_split(new_cmd[1], ' ');
	if (data->parser->cmd == NULL)
		return (error_msg("failure on split cmd"), 1);
	if (data->parser->infile == NULL)
		data->parser->infile = new_infile(new_cmd[0], type);
	else
		add_infile_back(&data->parser->infile, new_cmd[0], type);
	return (0);
}


/*function to handle input redirection (<) and heredoc (<<).
However the heredod still neds some implementation*/
int	handle_infile(t_data *data, int i, bool start_with_redirection)
{
	char		*type;

	if (data->cmd_table[i][1] == '<')
		type = "heredoc";
	else
		type = "infile";
	if (start_with_redirection == true)
	{
		if (handle_redirection_in(data, i, type) == 1)
			return (error_msg("failure on redirection in"), 1);
	}
	else
	{
		if (data->parser->infile == NULL)
			data->parser->infile = new_infile(data->cmd_table[i+1], type);
		else
			add_infile_back(&data->parser->infile, data->cmd_table[i + 1], type);
	}
	return (0);
}
