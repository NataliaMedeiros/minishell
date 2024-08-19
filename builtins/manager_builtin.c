/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:37 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/19 10:38:04 by edribeir      ########   odam.nl         */
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

bool	is_builtin(t_parser *parse_data, t_data *data)
{
	int	fd;

	fd = change_fd(parse_data);
	if (data->parser->cmd == NULL)
	{
		printf("data->parser->cmd is NULL\n");
		return (free_parsing(&data->parser),
			error_msg("data->parser->cmd is not initialized\n"), STDERR_FILENO);
	}
	if (ft_strncmp(parse_data->cmd[0], "echo", 4) == 0)
		return (echo_n(parse_data, fd), true);
	else if (ft_strncmp(parse_data->cmd[0], "pwd", 4) == 0)
		return (pwd(fd), true);
	else if (ft_strncmp(parse_data->cmd[0], "cd", 2) == 0)
		return (ft_cd(parse_data, data), true);
	else if (ft_strncmp(parse_data->cmd[0], "env\0", 4) == 0
		&& parse_data->cmd[1] == NULL)
		return (env_print(data, parse_data, fd), true);
	else if (ft_strncmp(parse_data->cmd[0], "unset", 5) == 0)
		return (ft_unset(&data->env, parse_data), true);
	else
		return (false);
	// falta o export and exit
}
