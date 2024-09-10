/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:20:29 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/10 12:40:10 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_lim_quotes(char *limiter)
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

static char	*remove_lim_backslash(char *limiter)
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

char	*find_limiter(t_parser **parser)
{
	char	*limiter;

	if (ft_strchr((*parser)->infile->name, '"') != NULL
		|| ft_strchr((*parser)->infile->name, '\'') != NULL)
		limiter = remove_lim_quotes((*parser)->infile->name);
	else if (ft_strchr((*parser)->infile->name, '\\') != NULL)
		limiter = remove_lim_backslash((*parser)->infile->name);
	else
		limiter = (*parser)->infile->name;
	return (limiter);
}

static void	heredoc_child(t_parser **parser, t_data *data)
{
	char	*line;
	char	*limiter;

	handle_signals(HEREDOC);
	(*parser)->fd_infile = open((*parser)->infile->name,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*parser)->fd_infile == -1)
		exit_with_msg("Fail to open infile\n", EXIT_FAILURE);
	limiter = find_limiter(parser);
	line = readline(">");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		while (ft_strchr(line, '$') != NULL)
			line = handle_dollar_sign(line, (*data));
		write((*parser)->fd_infile, line, strlen(line));
		write((*parser)->fd_infile, "\n", 1);
		free(line);
		line = readline(">");
	}
	close((*parser)->fd_infile);
	free(line);
	exit(EXIT_SUCCESS);
}

void	handle_heredoc(t_parser **parser, t_data *data)
{
	pid_t	pid_child;
	int		status;

	status = 0;
	pid_child = fork();
	if (pid_child < 0)
	{
		perror("Fork error");
		return ;
	}
	if (pid_child == 0)
		heredoc_child(parser, data);
	else
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid_child, &status, 0);
	}
	exit_status_helper(data, status);
	if (data->exit_code == 0)
		(*parser)->fd_infile = open((*parser)->infile->name, O_RDONLY, 0644);
}
