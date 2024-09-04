/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/04 15:27:45 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_echo(t_parser *parse, int fd, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strcmp(parse->cmd[1], "$?") == 0)
	{
		while (parse->cmd[1][i] != '\0')
		{
			if (parse->cmd[1][i] == '$' && parse->cmd[1][i + 1] == '?')
			{
				ft_putnbr_fd(data->exit_code, fd);
				ft_putchar_fd('\n', fd);
			}
			i++;
		}
	}
	else
	{
		if (parse->flag == true)
			ft_putstr_fd(parse->cmd[1], fd);
		else
			ft_putendl_fd(fd, parse->cmd[1]);
	}
	data->exit_code = 0;
}

void	echo_n(t_parser *parse, int fd, t_data *data)
{
	if (parse->cmd[1] != NULL)
	{
		put_echo(parse, fd, data);
	}
	else
	{
		ft_putendl_fd(fd, "");
	}
}
