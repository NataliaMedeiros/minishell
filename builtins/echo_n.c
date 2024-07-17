/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/17 15:26:02 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(t_parser *data)
{
	int fd;

	if (data->outfile == NULL)
		fd = 1;
	else 
		fd = data->fd_outfile;
	if (data->cmd[1] != NULL)
	{
		if (ft_strncmp(data->cmd[0], "echoo", 5) == 0)
		{
			printf("Command not Found\n");
			// exit(127);
		}
		else if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
		{
			if (data->flag == true)
				ft_putstr_fd(data->cmd[1], fd);
			else
				ft_putendl_fd(fd, data->cmd[1]);
		}
	}
	// else
	// 	printf("\n");
	// echo null new line
	// echo -n flag 1 return
}
