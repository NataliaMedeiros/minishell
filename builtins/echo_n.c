/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/29 12:11:35 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(t_parser *parse)
{
	int	fd;

	fd = change_fd(parse);
	if (parse->cmd[1] != NULL)
	{
		if (ft_strncmp(parse->cmd[0], "echoo", 5) == 0)
		{
			ft_putendl_fd(1, "Command not Found");
			// exit(127);
		}
		else if (ft_strncmp(parse->cmd[0], "echo", 4) == 0)
		{
			if (parse->flag == true)
				ft_putstr_fd(parse->cmd[1], fd);
			else
				ft_putendl_fd(fd, parse->cmd[1]);
		}
	}
	// else
	// 	printf("\n");
	// echo null new line
	// echo -n flag 1 return
}
