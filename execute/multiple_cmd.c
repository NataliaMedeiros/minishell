/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/19 13:27:37 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	first_pipe(int *fd, t_parser *temp)
{
	if (temp->fd_infile != -2)
	{
		if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
			perror("Problem Dup First Pipe");
		close(temp->fd_infile);
	}
	if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		perror("Problem Dup First Pipe");
}

static void	dup_manager(t_exec *exec, int i, t_parser *temp)
{
	if (i == 0)
		first_pipe(exec->fd, temp);
	else if (i == exec->nb_pipes)
	{
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
			close (temp->fd_outfile);
		}
		if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem Dup Last Prev");
	}
	else
	{
		if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem dup Prev");
		if (dup2(exec->fd[WRITE], STDOUT_FILENO) == -1)
			perror("Problem dup");
	}
	close(exec->fd[READ]);
	close(exec->fd[WRITE]);
}

void	child(t_exec *exec, t_data *data, t_parser *temp, int i)
{
	char	*path;

	path = cmd_path_checker(data, temp); // check if it is null ?
	dup_manager(exec, i, temp);
	if (is_builtin(temp, data) == false)
	{
		execve(path, temp->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, temp->cmd[0]);
		exit (127);
	}
	exit(EXIT_SUCCESS);
}

void	parent(t_exec *exec, pid_t pid_child)
{
	close(exec->fd[WRITE]);
	exec->prev_read = exec->fd[READ];
	waitpid(pid_child, &exec->status, 0);
}

int	pipeline(t_data *data, t_parser *parser, int nb_pipes)
{
	int			i;
	pid_t		pid_child;
	t_parser	*temp;
	t_exec		exec;

	exec.prev_read = STDIN_FILENO;
	exec.nb_pipes = nb_pipes;
	temp = parser;
	i = 0;
	while (temp)
	{
		if (pipe(exec.fd) < 0)
			return (perror("Pipe error"), EXIT_FAILURE);
		pid_child = fork();
		if (pid_child < 0)
			return (perror("Fork error"), EXIT_FAILURE);
		if (pid_child == 0)
			child(&exec, data, temp, i);
		else
			parent(&exec, pid_child);
		i++;
		temp = temp->pipe;
	}
	close(exec.prev_read);
	return (WEXITSTATUS(exec.status));
}
