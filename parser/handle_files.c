/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:10:34 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/12 11:34:07 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **split_out_and_cmd(char *cmd)
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
int handle_first_redirection_outfile(t_parser **parser, char **cmd_table, int i)
{
	char **temp;

	temp = split_out_and_cmd(cmd_table[i + 1]);
	(*parser)->cmd = ft_split(temp[1], ' ');
	if ((*parser)->cmd == NULL)
		return (1);
	(*parser)->outfile = ft_strdup(temp[0]);
	if ((*parser)->outfile == NULL)
		return (1);
	if (cmd_table[i][1] == '>')
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
int	handle_outfile(t_parser	**parser, char **cmd_table, int i, bool first_redirection)
{
	if (first_redirection == true)
		handle_first_redirection_outfile(parser, cmd_table, i);
	else
	{
		(*parser)->outfile = ft_strdup(cmd_table[i + 1]);
		if ((*parser)->outfile == NULL)
			return (1);
		if (cmd_table[i][1] == '>')
			(*parser)->fd_outfile = open((*parser)->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0664);
		else
			(*parser)->fd_outfile = open((*parser)->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*parser)->fd_outfile == -1)
			return (error_msg("Failure to open outfile\n"),
				free((*parser)->outfile), 1);
	}
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

/*function to handle input redirection (<) and heredoc (<<).
However the heredod still neds some implementation*/
int	handle_infile(t_parser	**parser, char **cmd_table, int i)
{
	char		*type;
	t_infile	*temp;

	if (cmd_table[i][1] == '<')
		type = "heredoc";
	else
		type = "infile";
	if ((*parser)->infile == NULL)
		(*parser)->infile = new_infile(cmd_table[i + 1], type);
	else
	{
		temp = (*parser)->infile;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_infile(cmd_table[i + 1], type);
	}
	return (0);
}

int	handle_files(t_parser	**parser, t_data data, int i)
{
	bool	first_redirection;

	first_redirection = false;
	if (i == 0)
		first_redirection = true;
	if (data.cmd_table[i][0] == '>')
	{
		if (handle_outfile(parser, data.cmd_table, i, first_redirection) != 0)
			return (1);
		i++;
	}
	else if (data.cmd_table[i][0] == '<')
	{
		if (handle_infile(parser, data.cmd_table, i) != 0)
			return (1);
		i++;
	}
	return (0);
}
