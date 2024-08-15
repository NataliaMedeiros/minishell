/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:10:34 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/15 11:17:03 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **split_redirection_first(char *cmd)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	temp = malloc(3 * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	temp[0] = ft_calloc((i + 1), sizeof(char));
	if (temp[0] == NULL)
		return (NULL);
	ft_strlcpy(temp[0], cmd, i + 1);
	i++;
	j = i;
	while (cmd[j] != '\0')
		j++;
	if (j > i)
	{
		temp[1] = ft_calloc((i + 1), sizeof(char));
		if (temp[1] == NULL)
			return (NULL);
		ft_strlcpy(temp[1], cmd + i, (j - i + 1));
	}
	else
		temp[1] = NULL;
	temp[3] = NULL;
	return(temp);
}

int handle_redirection_out(t_data *data, int i)
{
	char **temp;

	temp = split_redirection_first(data->cmd_table[i + 1]);
	if (temp == NULL)
		return (1);
	data->parser->cmd = ft_split(temp[1], ' ');
	if (data->parser->cmd == NULL)
		return (1);
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

t_infile	*new_infile(char *name, char *type)
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
void	add_infile_back(t_infile **head, char *name, char *type)
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
int	handle_redirection_in(t_data	*data, int i, char *type)
{
	// t_infile	*temp;
	char		**new_cmd;

	new_cmd = split_redirection_first(data->cmd_table[i + 1]);
	i = 0;
	data->parser->cmd = ft_split(new_cmd[1], ' ');
	if (data->parser->cmd == NULL)
		return (1);
	if (data->parser->infile == NULL)
		data->parser->infile = new_infile(new_cmd[0], type);
	else
	{
		add_infile_back(&data->parser->infile, new_cmd[0], type);
		// temp = data->parser->infile;
		// while (temp->next != NULL)
		// 	temp = temp->next;
		// temp->next = new_infile(new_cmd[0], type);
	}
	return (0);
}


/*function to handle input redirection (<) and heredoc (<<).
However the heredod still neds some implementation*/
int	handle_infile(t_data *data, int i, bool start_with_redirection)
{
	char		*type;
	// t_infile	*temp;

	if (data->cmd_table[i][1] == '<')
		type = "heredoc";
	else
		type = "infile";
	if (start_with_redirection == true)
	{
		if (handle_redirection_in(data, i, type) == 1)
			return (1);
	}
	else
	{
		if (data->parser->infile == NULL)
			data->parser->infile = new_infile(data->cmd_table[i+1], type);
		else
		{
			add_infile_back(&data->parser->infile, data->cmd_table[i + 1], type);
			// temp = data->parser->infile;
			// while (temp->next != NULL)
			// 	temp = temp->next;
			// temp->next = new_infile(data->cmd_table[i+1], type);
		}
	}
	return (0);
}

int	handle_files(t_data *data, int i)
{
	bool	start_with_redirection;

	start_with_redirection = false;
	if (i == 0)
		start_with_redirection = true;
	if (data->cmd_table[i][0] == '>')
	{
		if (handle_outfile(data, i, start_with_redirection) != 0)
			return (1);
		i++;
	}
	else if (data->cmd_table[i][0] == '<')
	{
		if (handle_infile(data, i, start_with_redirection) != 0)
			return (1);
		i++;
	}
	return (0);
}
