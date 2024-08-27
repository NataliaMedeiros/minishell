/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/27 11:20:51 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	first_cmd(int *fd, t_parser *temp)
{
	if (temp->fd_infile != -2)
	{
		if (temp->fd_infile == -1)
				return (EXIT_FAILURE);
		if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
			return (perror("Problem Dup First Pipe IN"), EXIT_FAILURE);
		close(temp->fd_infile);
	}
	if (temp->fd_outfile != -2)
	{
		if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
			return (perror("Problem Dup First Pipe OUT"), EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			return(perror("Problem Dup First Pipe"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	dup_manager(t_exec *exec, int i, t_parser *temp)
{
	if (i == 0)
	{
		if (first_cmd(exec->fd, temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (i == exec->nb_pipes)
	{
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				return(perror("Problem Dup Last OUT"), EXIT_FAILURE);
		}
		if (temp->fd_infile != -2)
		{
			if (temp->fd_infile == -1)
				return (EXIT_FAILURE);
			if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
				return (perror("Problem Dup Last IN"), EXIT_FAILURE);
			close(temp->fd_infile);
		}
		else
		{
			if (dup2(exec->prev_read, STDIN_FILENO) == -1)
				return (perror("Problem Dup Last Prev"), EXIT_FAILURE);
			close(exec->prev_read);
		}
	}
	else
	{
		if (temp->fd_infile != -2)
		{
			if (temp->fd_infile == -1)
				return (EXIT_FAILURE);
			if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
				return (perror("Problem Dup Last IN") , EXIT_FAILURE);
			close(temp->fd_infile);
		}
		else
		{
			if (dup2(exec->prev_read, STDIN_FILENO) == -1)
				return (perror("Problem dup Prev"), EXIT_FAILURE);
			close(exec->prev_read);
		}
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				return (perror("Problem Dup Last"), EXIT_FAILURE);
		}
		else
			if (dup2(exec->fd[WRITE], STDOUT_FILENO) == -1)
				return (perror("Problem dup"), EXIT_FAILURE);
		
	}
	close(exec->fd[READ]);
	close(exec->fd[WRITE]);
	return (EXIT_SUCCESS);
}

static void	child(t_exec *exec, t_data *data, t_parser *temp, int i)
{
	char	*path;

	path = cmd_path_checker(data, temp);
	if(dup_manager(exec, i, temp) == 1)
	{
		if (path != NULL)
			free(path);
		exit (EXIT_FAILURE);
	}
	if (is_builtin(temp, data) == false)
	{
		if (path != NULL)
			execve(path, temp->cmd, data->envp);
		ft_putstr_fd("Command NOT found: ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, temp->cmd[0]);
		if (path != NULL)
			free(path);
		exit (127);
	}
	if (path != NULL)
		free(path);
	exit(EXIT_SUCCESS);
}

void	parent(t_exec *exec, t_parser *temp)
{
	if (temp->fd_outfile != -2 && temp->fd_outfile != -1)
		close(temp->fd_outfile);
	if (temp->fd_infile != -2 && temp->fd_infile != -1)
		close(temp->fd_infile);
	close(exec->fd[WRITE]);
	if(exec->prev_read != STDIN_FILENO)
		close(exec->prev_read);
	exec->prev_read = exec->fd[READ];
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
		parent(&exec, temp);
		i++;
		temp = temp->pipe;
	}
	close(exec.prev_read);
	while(wait(NULL) != -1)
	{
		wait(NULL);
	}
	waitpid(pid_child, &exec.status, 0);
	return (WEXITSTATUS(exec.status));
}
