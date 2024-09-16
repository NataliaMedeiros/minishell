/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:20:29 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/13 18:05:57 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	line_exists(t_parser **parser, char *line, char *limiter, t_data *d)
{
	char	*temp;

	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		while (ft_strchr(line, '$'))
		{
			temp = handle_dollar_sign(line, (*d));
			free(line);
			line = ft_strdup(temp);
			free(temp);
		}
		write((*parser)->fd_infile, line, strlen(line));
		write((*parser)->fd_infile, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
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
	line_exists(parser, line, limiter, data);
	close((*parser)->fd_infile);
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
