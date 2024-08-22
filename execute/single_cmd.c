/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:53:46 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/22 17:47:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	checker_fd_dup(t_data *data)
{
	if (data->parser->fd_infile == -1)
		return (error_msg("No such file or directory"), false);
	if (data->parser->fd_infile != -2)
	{
		if (dup2(data->parser->fd_infile, STDIN_FILENO) == -1)
			perror("Problem Dup Single CMD IN");
		close(data->parser->fd_infile);
	}
	if (data->parser->fd_outfile != -2)
	{
		if (dup2(data->parser->fd_outfile, STDOUT_FILENO) == -1)
			perror("Problem Dup Single CMD OUT");
		close(data->parser->fd_outfile);
	}
	return (true);
}

int	one_cmd(t_data *data, char *path)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	if (pid_child == -1)
		error_msg("Problem forking");
	if (pid_child == 0)
	{
		if (checker_fd_dup(data) == false)
			return (EXIT_FAILURE);
		if (path != NULL)
			execve(path, data->parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, data->parser->cmd[0]);
		exit (127);
	}
	if (data->parser->fd_infile != -2)
		close(data->parser->fd_infile);
	if (data->parser->fd_outfile != -2)
		close(data->parser->fd_outfile);
	waitpid(pid_child, &status, 0);
	return (WEXITSTATUS(status));
}
