/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/30 11:42:49 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_infile(t_parser **parser, t_data *data)
{
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
}

void	write_space(char **temp, int *j)
{
	(*temp)[*j] = ' ';
	(*j)++;
}

void	fill_conditional(char **temp, int *j, int *i, char *str)
{
	if (*i != 0 && ft_isalpha(str[*i - 1]) == 1)
		write_space(temp, j);
	if (*i == 0 || ft_isalpha(str[*i + 1]) == 1)
	{
		(*temp)[*j] = str[*i];
		(*j)++;
		if ((str[*i] == '<' && str[*i + 1] != '<') || (str[*i] == '>' && str[*i + 1] != '>'))
			write_space(temp, j);
		else if (str[*i] == '|' && str[*i + 1] != ' ')
			write_space(temp, j);
		(*i)++;
	}
	// else if(ft_isalpha(str[*i - 1]) == 1)
	// 	write_space(temp, j);
	(*temp)[*j] = str[*i];
	(*j)++;
	if (((str[*i] == '<' && str[*i + 1] != '<')
		|| (str[*i] == '>' && str[*i + 1] != '>'))
		|| (str[*i] == '|' && (str[*i + 1] == '<' || str[*i + 1] == '>')))
		write_space(temp, j);
	(*i)++;
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
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			fill_conditional(&temp, &j, &i, str);
		else
		{
			temp[j] = str[i];
			j++;
			i++;
		}
	}
	printf("new str: %s\n", temp);
	return (temp);
}

void	create_infiles(t_parser **temp, t_data *data)
{
	while (*temp != NULL)
	{
		if ((*temp)->infile != NULL)
			exec_infile(temp, data);
		*temp = (*temp)->pipe;
	}
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
	create_infiles(&temp, data);
	print_struct(data->parser);
	//implement free parser
	return (0);
}

