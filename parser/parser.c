/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/07/25 14:05:10 by natalia       ########   odam.nl         */
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
		else if (data.cmd_lst[i][0] == '>' || data.cmd_lst[i][0] == '<')
		{
			if (handle_files(parser, data, i) != 0)
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

// void	exec_infile(t_parser **parser, t_data	data)
// {
// 	printf("Entrei no exec infile\n");
// 	if (ft_strcmp((*parser)->infile->type, "infile") == 0)
// 	{
// 		while ((*parser)->infile->next != NULL)
// 		{
// 			(*parser)->infile = (*parser)->infile->next;
// 		}
// 		(*parser)->fd_infile = open((*parser)->infile->name,
// 				O_RDONLY, 0644);
// 	}
// 	else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
// 	{
// 		while ((*parser)->infile->next != NULL)
// 		{
// 			handle_heredoc(parser, data);
// 			int i = close((*parser)->fd_infile);
// 			printf("close return: %d\n", i);
// 			(*parser)->infile = (*parser)->infile->next;
// 		}
// 		handle_heredoc(parser, data);
// 	}
// }

void	exec_infile(t_parser **parser, t_data	data)
{
	while ((*parser)->infile->next != NULL)
	{
		printf("infile type: %s\n", (*parser)->infile->type);
		if (ft_strcmp((*parser)->infile->type, "infile") == 0)
			(*parser)->fd_infile = open((*parser)->infile->name,
					O_RDONLY, 0644);
		else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		{
			handle_heredoc(parser, data);
			int i = close((*parser)->fd_infile);
			printf("close return: %d\n", i);
		}
		(*parser)->infile = (*parser)->infile->next;
	}
	printf("infile type: %s\n", (*parser)->infile->type);
	if (ft_strcmp((*parser)->infile->type, "infile") == 0)
		(*parser)->fd_infile = open((*parser)->infile->name,
				O_RDONLY, 0644);
	else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		handle_heredoc(parser, data);
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
	parser = new_struct();
	if (parser == NULL)
		return (error_msg_with_free("Failure on parsing\n", data.cmd_lst), 1);
	head_parser = parser;
	if (fill_parser(data, &parser) != 0)
		return (free_parsing(&parser), 1);
	if (parser->infile != NULL)
		exec_infile(&parser, data);
	print_struct(parser);
	//ver se é o lugar certo paraimplementar free struct when finish to use a cmd line and before return to prompt
	manager_functions(head_parser, &data);
	return (0);
}
