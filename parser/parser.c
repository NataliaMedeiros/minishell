/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/07/22 17:41:47 by nmedeiro      ########   odam.nl         */
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

/*function to handle output redirection (>) and append (>>)*/
int	handle_outfile(t_parser	**parser, char **cmd_lst, int i)
{
	(*parser)->outfile = ft_strdup(cmd_lst[i + 1]);
	if ((*parser)->outfile == NULL)
		return (1);
	if (cmd_lst[i][1] == '>')
		(*parser)->fd_outfile = open((*parser)->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		(*parser)->fd_outfile = open((*parser)->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*parser)->fd_outfile == -1)
		return (error_msg("Failure to open outfile\n"),
			free((*parser)->outfile),1); //testar o free aqui e dessa forma e escrever uma função para lhe dar com error e free
	return (0);
}

t_infile	*new_infile(char *name, char *type)
{
	t_infile	*new_element;

	new_element = malloc(sizeof(t_list));
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
	int i = 0;
	while (current_node->next != NULL)
	{
		i++;
		printf("%s and %d\n", current_node->type ,i);
		current_node = current_node->next;
	}
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	new_node = new_infile(name, type);
	current_node->next = new_node;
}

/*function to handle input redirection (<) and heredoc (<<).
However the heredod still neds some implementation*/
int	handle_infile(t_parser	**parser, t_data data, int i)
{
	char		*type;
	t_infile	*temp;

	if (data.cmd_lst[i][1] == '<')
		type = "heredoc";
	else
		type = "infile";
	if ((*parser)->infile == NULL)
		(*parser)->infile = new_infile(data.cmd_lst[i + 1], type);
	else
	{
		temp = (*parser)->infile;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_infile(data.cmd_lst[i + 1], type);
	}
	return (0);
}

int	fill_parser(t_data	data, t_parser	**parser)
{
	int	i;

	i = 0;
	while (data.cmd_lst[i] != NULL)
	{
		if (data.cmd_lst[i][0] == '|')
		{
			if (handle_pipe(parser) != 0)
				return (1);
		}
		else if (data.cmd_lst[i][0] == '>')
		{
			if (handle_outfile(parser, data.cmd_lst, i) != 0)
				return (1);
			i++;
		}
		else if (data.cmd_lst[i][0] == '<'/*&& data.cmd_lst[i][1] != '<'*/)
		{
			if (handle_infile(parser, data, i) != 0)
				return (1);
			i++;
		}
		else
			if (fill_cmd(parser, data, i) != 0)
				return (1);
		i++;
	}
	return (0);
}

/*Function that creates the parser struct
head is used to not lose the reference to the first node
print_struct será removido, pois está aqui somente para
imprimir e conferir struct*/
int	parser(t_data data)
{
	t_parser	*parser;
	t_parser	*head_parser;

	data.cmd_lst = split_cmds(data);
	if (data.cmd_lst == NULL)
		return (error_msg("Failure on parsing\n"), 1);
	print_array(data.cmd_lst);
	parser = new_struct();
	if (parser == NULL)
		return (error_msg_with_free("Failure on parsing\n", data.cmd_lst), 1);
	head_parser = parser;
	if (fill_parser(data, &parser) != 0)
		return (free_parsing(&parser), 1);
	print_struct(head_parser);
	//ver se é o lugar certo paraimplementar free struct when finish to use a cmd line and before return to prompt
	manager_functions(head_parser, &data);
	return (0);
}
