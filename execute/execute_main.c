/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/13 11:56:54 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int pipeline(t_data *data, char *path, t_parser *parse)
// {
	// 
// }

void	one_cmd(t_data *data, char *path, t_parser *parser)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	if (pid_child == -1)
		error_msg("Problem in fork");
	if (pid_child == 0)
	{
		dup2(data->parser->fd_infile, STDIN_FILENO);
		dup2(data->parser->fd_outfile, STDOUT_FILENO);
		close(data->parser->fd_infile);
		close(data->parser->fd_outfile);
		execve(path, parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, parser->cmd[0]);
		exit (127);
	}
	waitpid(pid_child, &status, 0);
}

int	ft_execute(t_data *data)
{
	char	*path;

	if (data->parser->nb_pipes == 0)
	{
		if (is_buildin(data->parser, data) == false)
		{
			path = absolute_path_checker(data);
			one_cmd(data, path, data->parser);
		}
	}
	// else if (data->parser->nb_pipes >= 1)
	// {
	// 	if (pipeline(data, path, data->parser) == 1)
	// 		error_msg("error piping");
	// }
	return (0);
}
