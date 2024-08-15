/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/15 17:50:25 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_manager(int *fd, int i, int nb_pipes, int prev_read, t_parser *temp)
{
	if (i == 0)
	{
		if (temp->fd_infile != -2)
			dup2(temp->fd_infile, STDIN_FILENO);
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			perror("noooo");
	}
	else if (i == nb_pipes)
	{
		if (temp->fd_outfile != -2)
			dup2(temp->fd_outfile, STDOUT_FILENO);
		dup2(prev_read, STDIN_FILENO);
	}
	else
	{
		dup2(prev_read, STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
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
			execve(path, temp->cmd, data->envp);
			ft_putstr_fd("Command not found: ", 2);
			ft_putendl_fd(2, temp->cmd[0]);
			exit (127);
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

void	one_cmd(t_data *data, char *path)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	if (pid_child == -1)
		error_msg("Problem forking");
	if (pid_child == 0)
	{
		if (data->parser->fd_infile != -2)
		{
			dup2(data->parser->fd_infile, STDIN_FILENO); // add check to dup 2 ?
			close(data->parser->fd_infile);
		}
		if(data->parser->fd_outfile != -2)
		{
			dup2(data->parser->fd_outfile, STDOUT_FILENO);
			close(data->parser->fd_outfile);
		}
		execve(path, data->parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, data->parser->cmd[0]);
		exit (127);
	}
	waitpid(pid_child, &status, 0);
	// exit(WEXITSTATUS(status));
}

int	ft_execute(t_data *data)
{
	char	*path;
	int		nb_pipes;

	nb_pipes = pipe_counter(data->parser);
	if (nb_pipes == 0)
	{
		if (is_buildin(data->parser, data) == false)
		{
			path = cmd_path_checker(data, data->parser);
			one_cmd(data, path);
		}
	}
	else if (nb_pipes >= 1)
	{
		pipeline(data, data->parser, nb_pipes);
		// if (pipeline(data, path, data->parser) == 1)
		// 	error_msg("error piping");
	}
	// if (data->parser->infile->name)
	// 	unlink(data->parser->infile->name); // this will be in the cleanup function in the main
	return (0);
}
