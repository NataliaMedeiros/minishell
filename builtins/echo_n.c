/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/15 17:20:02 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(t_parser *data)
{
	if (ft_strncmp(data->cmd[0], "echo", 4) != 0)
		error_msg("Command Not found");
	else if (data->cmd[1] != NULL)
	{
		if (data->flag == true)
			ft_putstr_fd(data->cmd[1], 1);
		else
			ft_putendl_fd(1, data->cmd[1]);
	}
	// else if ((ft_strncmp(data->cmd[0], "echo", 4) == 0 && data->cmd[1] == NULL))
	// 	printf("\n");
}
