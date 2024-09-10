/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:53:46 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/09 14:41:59 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	checker_fd_dup(t_data *data)
{
	if (data->parser->fd_infile == -1)
		return (false);
	if (data->parser->fd_infile != -2)
	{
		if (dup2(data->parser->fd_infile, STDIN_FILENO) == -1)
			return (perror("Problem Dup Single CMD IN"), false);
		close(data->parser->fd_infile);
	}
	if (data->parser->fd_outfile != -2 && data->parser->fd_outfile != -1)
	{
		if (dup2(data->parser->fd_outfile, STDOUT_FILENO) == -1)
			return (perror("Problem Dup Single CMD OUT"), false);
		close(data->parser->fd_outfile);
	}
	return (true);
}

void	handle_fd_infile(t_data **data)
{
	if ((*data)->parser->fd_infile != -2
		&& (*data)->parser->fd_infile != -1)
	{
		if (ft_strcmp((*data)->parser->infile->type, "infile") == 0)
			close((*data)->parser->fd_infile);
		else
		{
			unlink((*data)->parser->infile->name);
		}
	}
}

int	one_cmd(t_data *data, char *path)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	handle_signals(CHILD);
	if (pid_child == -1)
		error_msg("Problem forking");
	if (pid_child == 0)
	{
		if (checker_fd_dup(data) == false)
			return (EXIT_FAILURE);
		if (path != NULL)
			execve(path, data->parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, data->parser->cmd[0]);
		clean_helper(data, path);
		exit (127);
	}
	handle_fd_infile(&data);
	if (data->parser->fd_outfile != -2 && data->parser->fd_outfile != -1)
		close(data->parser->fd_outfile);
	waitpid(pid_child, &status, 0);
	return (WEXITSTATUS(status));
}
