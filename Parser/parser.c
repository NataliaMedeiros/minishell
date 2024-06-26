/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/26 13:08:21 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_pipe(t_parser **parser)
{
	(*parser)->pipe = new_struct();
	if ((*parser)->pipe == NULL)
	{
		printf("Failed to allocate memory for pipe\n");
		return (1);
	}
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
		(*parser)->fd_outfile = open((*parser)->outfile, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		(*parser)->fd_outfile = open((*parser)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*parser)->fd_outfile == -1)
		return(printf("Failure to open outfile\n"), free((*parser)->outfile),1); //testar o free aqui e dessa forma e escrever uma função para lhe dar com error e free
	printf("outfile: %s and fd: %d\n", (*parser)->outfile, (*parser)->fd_outfile);
	return (0);
}

/*function to handle input redirection (<) and heredoc (<<). However the heredod still neds some implementation*/
int	handle_infile(t_parser	**parser, char **cmd_lst, int i)
{
	(*parser)->infile = ft_strdup(cmd_lst[i + 1]);
	if ((*parser)->infile == NULL)
		return (1);
	if (cmd_lst[i][1] == '<')
	{
		handle_heredoc(parser);
	}
	else
		(*parser)->fd_infile = open((*parser)->infile, O_CREAT | O_RDONLY, 0644);
	if ((*parser)->fd_outfile == -1)
		return(printf("Failure to open infile\n"), free((*parser)->infile),1); //testar o free aqui e dessa forma e escrever uma função para lhe dar com error e free
	return (0);
}

char	*remove_quotes(char *limiter)
{
	char	*new_limiter;
	int		i;
	int		j;

	new_limiter = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (new_limiter == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (limiter[i] != '\0')
	{
		if (limiter[i] != '"' && limiter[i] != '\'')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

bool	has_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

int	fill_cmd_mode_echo(t_parser	**parser, char *cmd)
{
	char	*temp;

	printf("received cmd: %s\n", cmd);
	(*parser)->cmd = ft_calloc(sizeof(char *), 3);
	if ((*parser)->cmd == NULL)
		return (1);
	(*parser)->cmd[0] = ft_strdup("echo");
	if ((*parser)->cmd[0] == NULL)
		return (1);
	temp = ft_strtrim(cmd, "echo ");
	if (temp == NULL)
		return (1);
	printf("temp ->%s\n", temp);
	if (has_quotes(temp) == true)
		(*parser)->cmd[1] = remove_quotes(temp);
	else
		(*parser)->cmd[1] = ft_strdup(temp);
	if ((*parser)->cmd[1] == NULL)
		return (1);
	free(temp);
	return (0);
}

int	fill_cmd(t_parser **parser, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		fill_cmd_mode_echo(parser, cmd);
	else
		(*parser)->cmd = ft_split(cmd, ' '); //esse split nao funciona quando é passado um texto como parametro (echo "hello word")
	return (0);
}

int	fill_parser(t_data	data, t_parser	**parser)
{
	int i;

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
		else if(data.cmd_lst[i][0] == '<')
		{
			if (handle_infile(parser, data.cmd_lst, i) != 0)
				return (1);
			i++;
		}
		else
			fill_cmd(parser, data.cmd_lst[i]);
		i++;
	}
	return (0);
}

/*Function that creates the parser struct*/
int	parser(t_data data)
{
	t_parser	*parser;
	t_parser	*head_parser; //head is used to not lose the reference to the first node

	data.cmd_lst = split_cmds(data);
	if (data.cmd_lst == NULL)
		return (1);
	parser = new_struct();
	if (parser == NULL)
		return (free_array(0, data.cmd_lst), 1); //free because split allocate memory
	head_parser = parser;
	if (fill_parser(data, &parser) != 0)
		return (1); //incluir free do parser
	print_struct(head_parser); //a linha será removida, pois está aqui somente para imprimir e conferir struct
	//implementar free struct when finish to use a cmd line and before return to prompt
	return (0);
}

