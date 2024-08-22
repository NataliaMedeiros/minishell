/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/21 18:28:37 by edribeir      ########   odam.nl         */
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
	while (data.cmd_table[i] != NULL)
	{
		if (data.cmd_table[i][0] == '|')
		{
			if (handle_pipe(parser) != 0)
				return (1);
		}
		else if (data.cmd_table[i][0] == '>' || data.cmd_table[i][0] == '<')
		{
			if (handle_files(parser, data, i) != 0)
				return (1);
			i++;
		}
		else
		{
			if (fill_cmd(parser, data, i) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	exec_infile(t_parser **parser, t_data data)
{
	while ((*parser)->infile->next != NULL)
	{
		printf("infile type: %s\n", (*parser)->infile->type);
		if (ft_strcmp((*parser)->infile->type, "infile") == 0)
			(*parser)->fd_infile = open((*parser)->infile->name,
					O_RDONLY, 0644);
		else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		{
			// (*parser)->fd_infile = open((*parser)->infile->name,
			// 		O_CREAT | O_WRONLY | O_TRUNC, 0644);
			// printf("open return: %d\n", (*parser)->fd_infile);
			// if ((*parser)->fd_infile == -1)
			// 	return (error_msg("Fail to open infile\n"));
			handle_heredoc(parser, data);
			// close((*parser)->fd_infile);
		}
		(*parser)->infile = (*parser)->infile->next;
	}
	if (ft_strcmp((*parser)->infile->type, "infile") == 0)
		(*parser)->fd_infile = open((*parser)->infile->name,
				O_RDONLY, 0644);
	else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		handle_heredoc(parser, data);
}

/*Function creates parser struct*/
int	parser(t_data *data)
{
	t_parser	*head_parser;

	data->cmd_table = split_cmds(*data);
	if (data->cmd_table == NULL)
		return (error_msg("Failure on create cmd list\n"), 1);
	// print_array(data->cmd_table);
	data->parser = new_struct();
	if (data->parser == NULL)
		return (error_msg_with_free("Failure on create parsing struct\n",
				data->cmd_table), 1);
	head_parser = data->parser;
	if (fill_parser((*data), &head_parser) != 0)
		return (free_parsing(&head_parser),
			error_msg("Failure on parsing\n"), 1);
	if (data->parser->infile != NULL)
		exec_infile(&data->parser, (*data));
	// print_array(data->parser->cmd);
	// print_struct(data->parser);
	//free_array(0, &data.cmd_line);
	//implement free parser
	return (0);
}

