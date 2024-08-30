/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/30 15:29:35 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(t_parser *parse, int fd, t_data *data)
{
	if (parse->cmd[1] != NULL)
	{
		if (ft_strncmp(parse->cmd[0], "echoo", 5) == 0)
		{
			ft_putendl_fd(STDERR_FILENO, "Command not Found");
			// exit(127);
		}
		else if (ft_strncmp(parse->cmd[0], "echo", 4) == 0)
		{
			if (parse->flag == true)
				ft_putstr_fd(parse->cmd[1], fd);
			else
				ft_putendl_fd(fd, parse->cmd[1]);
			data->exit_code = 0;
		}
	}
	else
	{

		if (ft_strncmp(parse->cmd[0], "echoo", 5) == 0)
			ft_putendl_fd(STDERR_FILENO, "Command not Found");
		else
			ft_putendl_fd(fd, "");
	}
}
