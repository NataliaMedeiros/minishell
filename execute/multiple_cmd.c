/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:54:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/16 16:42:27 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	first_pipe(int *fd, t_parser *temp)
{
	if (temp->fd_infile != -2)
		if (dup2(temp->fd_infile, STDIN_FILENO) == -1)
			perror("Problem Dup First Pipe");
	if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		perror("Problem Dup First Pipe");
}

static void	dup_manager(int *fd, int i, int nb_pipes, int prev_read, t_parser *temp)
{
	if (i == 0)
		first_pipe(fd, temp);
	else if (i == nb_pipes)
	{
		if (temp->fd_outfile != -2)
			if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
				perror("Problem Dup Last");
		if (dup2(prev_read, STDIN_FILENO) == -1)
			perror("Problem Dup Last Prev");
	}
	else
	{
		if (dup2(prev_read, STDIN_FILENO) == -1)
			perror("Problem dup Prev");
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			perror("Problem dup");
	}
	close(fd[READ]);
	close(fd[WRITE]);
	// if (prev_read != STDIN_FILENO)
	// 	close(prev_read);
}

void	pipeline(t_data *data, t_parser *parser, int nb_pipes)
{
	char		*path;
	int			i;
	int			fd[2];
	pid_t		pd_child;
	int			status;
	t_parser	*temp;
	int			prev_read;

	prev_read = STDIN_FILENO;
	temp = parser;
	i = 0;
	while (temp)
	{
		path = cmd_path_checker(data, temp);
		if (pipe(fd) < 0)
		{
			error_msg("error pipe");
			exit(EXIT_FAILURE);
		}
		pd_child = fork();
		if (pd_child < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		if (pd_child == 0)
		{
			dup_manager(fd, i, nb_pipes, prev_read, temp);
			if (is_builtin(temp, data) == false)
			{
				execve(path, temp->cmd, data->envp);
				ft_putstr_fd("Command not found: ", 2);
				ft_putendl_fd(2, temp->cmd[0]);
				exit (127);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[WRITE]);
			// if (prev_read != STDIN_FILENO)
			// 	close(prev_read);
			prev_read = fd[READ];
			waitpid(pd_child, &status, 0);
		}
		i++;
		temp = temp->pipe;
	}
	close(prev_read);
	// exit(WEXITSTATUS(status));
}
