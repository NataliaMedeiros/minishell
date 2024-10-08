/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/13 16:35:18 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dup_manager(t_exec *exec, int i, t_parser *temp)
{
	if (i == 0)
	{
		if (first_cmd(exec->fd, temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (i == exec->nb_pipes)
	{
		if (last_cmd(temp, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (middle_cmd(temp, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	close(exec->fd[READ]);
	close(exec->fd[WRITE]);
	return (EXIT_SUCCESS);
}

static void	child(t_exec *exec, t_data *data, t_parser *temp)
{
	char	*path;

	path = cmd_path_checker(data, temp);
	if (dup_manager(exec, exec->i, temp) == 1)
	{
		close(exec->fd[READ]);
		close(exec->fd[WRITE]);
		if (exec->prev_read != STDIN_FILENO)
			close(exec->prev_read);
		clean_helper(data, path);
		exit (EXIT_FAILURE);
	}
	if (is_builtin(temp, data) == false)
	{
		if (path != NULL)
			execve(path, temp->cmd, data->envp);
		ft_putendl_fd(STDERR_FILENO, "Command not found");
		clean_helper(data, path);
		exit (127);
	}
	clean_helper(data, path);
	exit(EXIT_SUCCESS);
}

void	parent(t_exec *exec, t_parser *temp)
{
	if (temp->fd_outfile != -2 && temp->fd_outfile != -1)
		close(temp->fd_outfile);
	if (temp->fd_infile != -2 && temp->fd_infile != -1)
		close(temp->fd_infile);
	close(exec->fd[WRITE]);
	if (exec->prev_read != STDIN_FILENO)
		close(exec->prev_read);
	exec->prev_read = exec->fd[READ];
}

int	pipe_and_fork(t_exec *exec)
{
	if (pipe(exec->fd) < 0)
		return (perror("Pipe error"), EXIT_FAILURE);
	exec->pid_child = fork();
	if (exec->pid_child < 0)
		return (perror("Fork error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	pipeline(t_data *data, t_parser *parser, int nb_pipes)
{
	t_parser	*temp;
	t_exec		exec;

	exec.prev_read = STDIN_FILENO;
	exec.nb_pipes = nb_pipes;
	temp = parser;
	exec.i = 0;
	while (temp != NULL)
	{
		if (pipe_and_fork(&exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		handle_signals(CHILD);
		if (exec.pid_child == 0)
			child(&exec, data, temp);
		parent(&exec, temp);
		if (data->exit_code == 130)
			break ;
		exec.i++;
		temp = temp->pipe;
	}
	close(exec.prev_read);
	waitpid(exec.pid_child, &exec.status, 0);
	exit_status_helper(data, exec.status);
	ft_waiting(exec);
	return (data->exit_code);
}
