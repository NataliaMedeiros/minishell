/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:17:35 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/30 15:00:37 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//need to exit and free everything, just received number arguments

void	ft_exit(t_data **data, t_parser *parser)
{
	if ((ft_strcmp(parser->cmd[0], "exit") == 0) && parser->cmd[1] == NULL)
		exit((*data)->exit_code);
	if (parser->cmd[2] != NULL)
	{
		ft_putstr_fd("to many argments\n", 2);
	}
	// else
	// {
	// 	ft_putstr_fd("exit\n", 2);
	// 	code = ft_atoi_long(cmd[1], mini, cmd, 0);
	// 	if (code == -1)
	// 		exit(mini->exit_code);
	// 	code = code % 256;
	// 	mini->exit_code = code;
	// 	exit(code);
	// }
}
