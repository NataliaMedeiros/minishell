/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:27:23 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/17 12:08:01 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_echo(t_parser *parser, int fd, t_data *data)
{
	int	i;

	i = 0;
	while (parser->cmd[1][i] != '\0')
	{
		if (parser->cmd[1][i] == '$' && parser->cmd[1][i + 1] == '?')
		{
			ft_putnbr_fd(data->exit_code, fd);
			i++;
		}
		else
			ft_putchar_fd(parser->cmd[1][i], fd);
		i++;
	}
	if (parser->flag == false)
		ft_putchar_fd('\n', fd);
	data->exit_code = 0;
}

void	echo_n(t_parser *parser, int fd, t_data *data)
{
	if (parser->cmd[1] != NULL)
	{
		put_echo(parser, fd, data);
	}
	else
	{
		ft_putendl_fd(fd, "");
	}
}
