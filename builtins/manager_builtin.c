/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:37 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/12 16:33:50 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_fd(t_parser *parser)
{
	int	fd;

	if (parser->outfile == NULL)
		fd = STDOUT_FILENO;
	else
		fd = parser->fd_outfile;
	return (fd);
}

bool	is_cmd_null(t_parser *parser, t_data *data)
{
	if (parser->cmd == NULL)
	{
		if (parser->fd_outfile != -2 && parser->fd_outfile != -1)
			close(parser->fd_outfile);
		if (parser->infile != NULL)
			handle_fd_infile(&data);
		return (true);
	}
	return (false);
}

bool	is_builtin(t_parser *parser, t_data *data)
{
	int	fd;

	fd = change_fd(parser);
	if (is_cmd_null(parser, data) == true)
		return (true);
	if (ft_strcmp(parser->cmd[0], "echo") == 0)
		return (echo_n(parser, fd, data), true);
	else if (ft_strcmp(parser->cmd[0], "pwd") == 0)
		return (ft_pwd(fd, parser, data), true);
	else if (ft_strcmp(parser->cmd[0], "cd") == 0)
		return (ft_cd(parser, data), true);
	else if (ft_strcmp(parser->cmd[0], "env") == 0)
		return (env_print(data, parser, fd), true);
	else if (ft_strcmp(parser->cmd[0], "unset") == 0)
		return (ft_unset(&data->env, parser, data), true);
	else if (ft_strcmp(parser->cmd[0], "export") == 0)
		return (ft_export(&data->env, parser, fd, data), true);
	else if (ft_strcmp(parser->cmd[0], "exit") == 0)
		return (ft_exit(data, parser), true);
	else
		return (false);
}
