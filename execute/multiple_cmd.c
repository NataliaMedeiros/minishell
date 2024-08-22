/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/22 14:59:52 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	first_pipe(int *fd, t_parser *temp)
{
	printf("%d  and fd[write] %d<<<<<<<<<<<<<<<<<<<\n", temp->fd_infile, fd[WRITE]);
	// if (temp->fd_infile != -2)
	// {
	// 	if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
	// 		perror("Problem Dup First Pipe");
	// 	// close(temp->fd_infile);
	// }
	// if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
	// 	perror("Problem Dup First Pipe");

	if (temp->fd_infile != -2)
	{
		ft_putstr_fd("\nfirst cmd opening pipe, infile\n", STDERR_FILENO);
		ft_putnbr_fd(temp->fd_infile, STDERR_FILENO);
		if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
			perror("--Problem Dup First Pipe IN");
		// close(temp->fd_infile);
	}
	if (temp->fd_outfile != -2)
	{
		ft_putstr_fd("\nfirst cmd with pipe, outfile\n", STDERR_FILENO);
		ft_putnbr_fd(temp->fd_outfile, STDERR_FILENO);
		if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
			perror("Problem Dup First Pipe OUT");
		// close(temp->fd_outfile); -> tem que estar aberto para functionar
	}
	else
	{
		ft_putstr_fd("\nfirst cmd no fd outfile\n", STDERR_FILENO);
		ft_putnbr_fd(fd[WRITE], STDERR_FILENO);
		ft_putstr_fd("\n\n", STDERR_FILENO);
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			perror("Problem Dup First Pipe");
		// close(fd[WRITE]);
	}
}

static void	dup_manager(int *fd, t_exec *exec, int i, t_parser *temp)
{
	if (i == 0)
		first_pipe(fd, temp);
	else if (i == exec->nb_pipes)
	{
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
			close (temp->fd_outfile);
		}
		ft_putstr_fd("\nThis Prev Read last pipe\n", STDERR_FILENO);
		ft_putnbr_fd(exec->prev_read, STDERR_FILENO);
		if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem Dup Last Prev");
		ft_putstr_fd("\nthis is STDIN LAST PIPE\n", STDERR_FILENO);
		ft_putnbr_fd(STDIN_FILENO, STDERR_FILENO);
		
	}
	else
	{

		if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem dup Prev");
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
			close (temp->fd_outfile);
		}
		else
			if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
				perror("Problem dup");
		
	}
	close(exec->fd[READ]);
	close(exec->fd[WRITE]);
}

void	child(int *fd, t_exec *exec, t_data *data, t_parser *temp, int i)
{
	char	*path;

	path = cmd_path_checker(data, temp);
	dup_manager(fd, exec, i, temp);
	if (is_builtin(temp, data) == false)
	{
		// ft_putnbr_fd(STDIN_FILENO, STDERR_FILENO);
		// ft_putnbr_fd(STDOUT_FILENO, STDERR_FILENO);
		if (path != NULL)
			execve(path, temp->cmd, data->envp);
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(2, temp->cmd[0]);
		if (path != NULL)
			free(path);
		exit (127);
	}
	if (path != NULL)
		free(path);
	exit(EXIT_SUCCESS);
}

void	parent(int *fd, t_exec *exec, pid_t pid_child)
{
	close(fd[WRITE]);
	if(exec->prev_read != STDIN_FILENO)
		close(exec->prev_read);
	exec->prev_read = fd[READ];
	waitpid(pid_child, &exec->status, 0);
}

int	pipeline(t_data *data, t_parser *parser, int nb_pipes)
{
	int			i;
	pid_t		pid_child;
	t_parser	*temp;
	int			fd[2];
	t_exec		exec;

	exec.prev_read = STDIN_FILENO;
	exec.nb_pipes = nb_pipes;
	temp = parser;
	i = 0;
	while (temp)
	{
		if (pipe(fd) < 0)
			return (perror("Pipe error"), EXIT_FAILURE);
		pid_child = fork();
		if (pid_child < 0)
			return (perror("Fork error"), EXIT_FAILURE);
		if (pid_child == 0)
			child(fd, &exec, data, temp, i);
		else
			parent(fd, &exec, pid_child);
		i++;
		// printf("bla\n");
		temp = temp->pipe;
	}
	close(exec.prev_read);
	return (WEXITSTATUS(exec.status));
}
