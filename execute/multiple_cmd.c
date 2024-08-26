/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/21 16:05:33 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	first_pipe(int *fd, t_parser *temp)
// {
// 	if (temp->fd_infile != -2)
// 	{
// 		if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
// 			perror("--Problem Dup First Pipe");
// 		// close(temp->fd_infile);
// 	}
// 	if (temp->fd_outfile != -2)
// 	{
// 		if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
// 			perror("Problem Dup Last");
// 		// close(temp->fd_outfile); -> tem que estar aberto para functionar
// 	}
// 	else
// 	{
// 		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
// 			perror("Problem Dup First Pipe");
// 		close(fd[WRITE]); //chat
// 	}
// }

static void	dup_manager(t_exec *exec, int i, t_parser *temp)
{
	if (i == 0)
	{
		if (temp->fd_infile != -2)
		{
			if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
				perror("--Problem Dup First Pipe");
			// close(temp->fd_infile);
		}
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
			
			// close(temp->fd_outfile); -> tem que estar aberto para functionar
		}
		else
		{
			if (dup2(exec->fd[WRITE], STDOUT_FILENO) == -1)
				perror("Problem Dup First Pipe");
		}
	}
	else if (i == exec->nb_pipes)
	{
		printf("to no fim\n");
		if (temp->fd_outfile != -2)
		{
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
			// close (temp->fd_outfile);
		}
		if (temp->fd_infile != -2)
		{
			if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
				perror("--Problem Dup First Pipe");
			close(temp->fd_infile);
		}
		else if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem Dup Last Prev");
		// close(exec->prev_read); //chat
	}
	else
	{
		printf("To no meio\n");
			// printf("%s\n", get_next_line(exec->prev_read));
		if (dup2(exec->prev_read, STDIN_FILENO) == -1)
			perror("Problem dup Prev");
		if (dup2(exec->fd[WRITE], STDOUT_FILENO) == -1)
			perror("Problem dup");
		close(exec->fd[WRITE]);
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
		free(path);
		exit (127);
	}
	free(path);
	exit(EXIT_SUCCESS);
}

void	parent(t_exec *exec, pid_t pid_child)
{
	close(exec->fd[WRITE]); //chat
	exec->prev_read = exec->fd[READ];
	waitpid(pid_child, &exec->status, 0);
}

int	pipeline(t_data *data, t_parser *parser, int nb_pipes)
{
	int			i;
	pid_t		pid_child;
	t_parser	*temp;
	t_exec		exec;

	// if (parser->fd_infile == -2)
	// {
	// 	exec.prev_read = parser->fd_infile;
	// }
	// else
		exec.prev_read = STDIN_FILENO;
	exec.nb_pipes = nb_pipes;
	temp = parser;
	i = 0;
	while (temp)
	{
		printf("HELLO\n");
		if (pipe(exec.fd) < 0)
			return (perror("Pipe error"), EXIT_FAILURE);
		pid_child = fork();
		if (pid_child < 0)
			return (perror("Fork error"), EXIT_FAILURE);
		if (pid_child == 0)
			child(&exec, data, temp, i);
		parent(&exec, pid_child);
		i++;
		temp = temp->pipe;
	}
	// wait(NULL);
	close(exec.prev_read);
	return (WEXITSTATUS(exec.status));
}
