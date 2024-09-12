/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 10:49:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/10 13:58:38 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_cmd(int *fd, t_parser *temp)
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
			return (perror("Problem Dup First Pipe"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	last_cmd(t_parser *temp, t_exec *exec)
{
	if (temp->fd_outfile != -2)
	{
		if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
			return (perror("Problem Dup Last OUT"), EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

int	middle_cmd(t_parser *temp, t_exec *exec)
{
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
			return (perror("Problem dup Prev"), EXIT_FAILURE);
		close(exec->prev_read);
	}
	if (temp->fd_outfile != -2)
	{
		if (dup2(temp->fd_outfile, STDOUT_FILENO) == -1)
			return (perror("Problem Dup Last"), EXIT_FAILURE);
	}
	else
	{
		if (dup2(exec->fd[WRITE], STDOUT_FILENO) == -1)
			return (perror("Problem dup"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	clean_helper(t_data *data, char *path)
{
	if (path != NULL)
		free(path);
	if (data->env != NULL)
		free_env(&data->env);
	cleanup(data);
}

void	ft_waiting(t_exec exec)
{
	while (waitpid(-1, &exec.status, 0) > 0)
	{
	}
}
