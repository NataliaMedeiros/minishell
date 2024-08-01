/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/01 13:06:37 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent(t_data *data, char *path, t_parser *parser)
{
	int		fd_pipe[2];
	pid_t	pid_child;
	int		status;

	pipe(fd_pipe);
	pid_child = fork();
	if (pid_child == 0)
	{
		// dup2(fd_pipe[WRITE], STDOUT_FILENO);
		// close(fd_pipe[READ]);
		execve(path, parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, parser->cmd[0]);
	}
	close(fd_pipe[READ]);
	close(fd_pipe[WRITE]);
	waitpid(pid_child, &status, 0);
}

int	ft_execute(t_data *data)
{
	char	*path;

	if (is_buildin(data->parser, data) == false)
	{
		path = check_path(data);
		parent(data, path, data->parser);
	}
	return (0);
}
