/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/28 15:32:08 by nmedeiro      ########   odam.nl         */
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
	int		i;
	bool	has_pipe;
	bool	start_with_redirection;

	i = 0;
	has_pipe = false;
	while (data.cmd_table[i] != NULL)
	{
		start_with_redirection = false;
		if (data.cmd_table[i][0] == '|')
		{
			if (handle_pipe(parser) != 0)
				return (error_msg("failure on handle pipe"), 1);
			has_pipe = true;
		}
		else if (data.cmd_table[i][0] == '>' || data.cmd_table[i][0] == '<')
		{
			if (i == 0)
				start_with_redirection = true;
			else if (has_pipe == true)
				start_with_redirection = true;
			if (handle_files(data, parser, i, start_with_redirection) != 0)
				return (error_msg("failure on handle files"), 1);
			i++;
			// if (data.cmd_table[i + 1] != NULL)
			// 	i++;
			has_pipe = false;
		}
		else
		{
			if (fill_cmd(parser, data, i) != 0)
				return (error_msg("failure on fill cmd"), 1);
			has_pipe = false;
		}
		i++;
	}
	return (0);
}

void	exec_infile(t_parser **parser, t_data *data)
{
	while ((*parser)->infile->next != NULL)
	{
		if (ft_strcmp((*parser)->infile->type, "infile") == 0)
		{
			// printf("ENTREI AQUI haha333333\n<<<<<");
			(*parser)->fd_infile = open((*parser)->infile->name,
					O_RDONLY, 0644);
			// printf("fd infile %d<<<<\n", (*parser)->fd_infile);
		}
		else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
			handle_heredoc(parser, data);

		(*parser)->infile = (*parser)->infile->next;
	}
	if (ft_strcmp((*parser)->infile->type, "infile") == 0)
	{
		(*parser)->fd_infile = open((*parser)->infile->name,
				O_RDONLY, 0644);
	}
	else if (ft_strcmp((*parser)->infile->type, "heredoc") == 0)
		handle_heredoc(parser, data);
}

char	*add_spaces(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_calloc((3 * ft_strlen(str) + 1), sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (i == 0 /*|| ft_isalpha(str[i + 1]) == 1*/))
		{
			temp[j] = str[i];
			j++;
			if ((str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
			{
				temp[j] = ' ';
				j++;
			}
			i++;
		}
		else
		{
			temp[j] = str[i];
			j++;
			i++;
		}
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if(ft_isalpha(str[i - 1]) == 1)
			{
				temp[j] = ' ';
				j++;
			}
			temp[j] = str[i];
			j++;
			i++;
			if (ft_isalpha(str[i]) == 1)
			{
				temp[j] = ' ';
				j++;
			}
			if ((str[i] == '<' && str[i + 1] != '<') && (str[i] == '>' && str[i + 1] != '>'))
			{
				temp[j] = ' ';
				j++;
			}
			if (str[i - 1] == '|' && (str[i] == '<' || str[i] == '>'))
			{
				temp[j] = ' ';
				j++;
			}
		}
	}
	printf("new str: %s\n", temp);
	return (temp);
}

/*Function creates parser struct*/
int	parser(t_data *data)
{
	t_parser	*head_parser;
	t_parser	*temp;
	char		*cmd_line;

	cmd_line = ft_calloc((strlen(data->cmd_line) + 1), sizeof(char));
	if (cmd_line == NULL)
		return (error_msg("Failure to malloc word\n"), 1);
	ft_strcpy(cmd_line, data->cmd_line);
	free(data->cmd_line);
	data->cmd_line = add_spaces(cmd_line);
	data->cmd_table = split_cmds(*data);
	// print_array(data->cmd_table);
	if (data->cmd_table == NULL)
		return (error_msg("Failure on create cmd list\n"), 1); // free
	data->parser = new_struct();
	if (data->parser == NULL)
		return (error_msg_with_free("Failure on create parsing struct\n",
				data->cmd_table), 1);
	head_parser = data->parser;
	if (fill_parser((*data), &head_parser) != 0)
		return (free_parsing(&head_parser),
			error_msg("Failure on parsing\n"), 1);
	temp = data->parser;
	while (temp != NULL)
	{
		if (temp->infile != NULL)
			exec_infile(&temp, data);
		temp = temp->pipe;
	}
	print_struct(data->parser);
	//free_array(0, &data.cmd_line);
	//implement free parser
	return (0);
}

