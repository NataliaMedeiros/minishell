/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/16 18:20:28 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(t_parser *data)
{
	if (data->cmd[1] != NULL)
	{
		if (ft_strncmp(data->cmd[0], "echoo", 5) == 0)
		{
			printf("Command not Found\n");
			// exit(127);
		}
		else if (ft_strncmp(data->cmd[1], "-n", 2) == 0)
			return ;
		else if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
		{
			if (data->flag == true)
				ft_putstr_fd(data->cmd[1], 1);
			else
				ft_putendl_fd(1, data->cmd[1]);
		}
	}
	// else
	// 	printf("\n");
}
