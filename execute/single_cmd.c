/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:53:46 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/20 18:53:38 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	checker_fd_dup(t_data *data)
{
	if (data->parser->fd_infile != -2)
	{
		if (dup2(data->parser->fd_infile, STDIN_FILENO) == -1)
			perror("Problem Dup Single CMD IN");
	}
	if (data->parser->fd_outfile != -2)
	{
		if (dup2(data->parser->fd_outfile, STDOUT_FILENO) == -1)
			perror("Problem Dup Single CMD OUT");
	}
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
		checker_fd_dup(data);
		if (path != NULL)
			execve(path, data->parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, data->parser->cmd[0]);
		exit (127);
	}
	waitpid(pid_child, &status, 0);
	return (WEXITSTATUS(status));
}
