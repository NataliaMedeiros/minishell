/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/25 13:47:15 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_commands(char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] == '<')
		{
			count += 2;
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i += 1;
		}
		i++;
	}
	return (count);
}

void	free_array(int	counter, char **cmd)
{
	if (counter == 0)
	{
		while (cmd[counter] != NULL)
		{
			free(cmd[counter]);
			counter++;
		}
	}
	else
	{
		while (counter > 0)
		{
			free(cmd[counter]);
			counter--;
		}
	}
	free(cmd);
}

/*this substring was modified to remove space on the beginning*/
char	*ft_substr_modified(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[start] == ' ')
		start++;
	if (ft_strlen(s) <= len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) == 1 || start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	substring = malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	**split_cmds(t_data data)
{
	int		nb_args;
	int		counter;
	int		i;
	int		start;
	char	**cmd;

	nb_args = nb_commands(data.command_line);
	cmd = ft_calloc((nb_args + 1), sizeof(char *));
	if (cmd == NULL)
		return (NULL);
	counter = 0;
	i = 0;
	while (counter < nb_args)
	{
		start = i;
		while (data.command_line[i] != '\0' && data.command_line[i] != '|'
				&& data.command_line[i] != '>' && data.command_line[i] != '<')
			i++;
		cmd[counter] = ft_substr_modified(data.command_line, start, (i - start));
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		start = i;
		if (counter == nb_args)
			break;
		if (data.command_line[i] == '>' || data.command_line[i] == '<')
			i++;
		cmd[counter] = ft_substr(data.command_line, start, (i + 1 - start));
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		i++;
	}
	cmd[counter] = NULL;
	return (cmd);
}

void	print_array(char **array)
{
	int i;

	i = 0;
	while(array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_struct(t_parser	*head)
{
	int	i;

	i = 1;
	printf("printing mini:\n");
	while (head != NULL)
	{
		printf("struct[%d]:\n", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("outfile: %s\n", head->outfile ? head->outfile : "None");
		printf("infile: %s\n", head->infile ? head->infile : "None");
		head = head->pipe;
		i++;
	}
}

t_parser	*new_struct()
{
	t_parser	*new_element;

	new_element = malloc(sizeof(t_parser));
	if (new_element == NULL)
		return (NULL);
	new_element->infile = NULL;
	new_element->outfile = NULL;
	new_element->pipe = NULL;
	return (new_element);
}

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

/*This functions remove quotes (simple or double) of the heredoc limiter*/
char	*remove_lim_quotes(char *limiter)
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

/*This functions remove backslash of the heredoc limiter
- Check if we should handle this, because I checked on bash and it removes the backslash*/
char	*remove_lim_backslash(char *limiter)
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
		if (limiter[i] != '\\')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

int	handle_heredoc(t_parser **parser)
{
	char	*line;
	char	*limiter;

	(*parser)->fd_infile = open((*parser)->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644); //revisar flags e permissoes. Pensar na parte do terminal
	if (ft_strchr((*parser)->infile, '"') != NULL || ft_strchr((*parser)->infile, '\'') != NULL)
		limiter = remove_lim_quotes((*parser)->infile);
	else if (ft_strchr((*parser)->infile, '\\') != NULL)
		limiter = remove_lim_backslash((*parser)->infile);
	else
		limiter = (*parser)->infile; //checar se compensa deixar assim ou usar o strdup(cmd_lst[i+1])
	printf("limiter: %s\n", limiter);
	line = readline(">");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter) &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		line = readline(">");
	}
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
			(*parser)->cmd = ft_split(data.cmd_lst[i], ' ');
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
	return (0);
}

